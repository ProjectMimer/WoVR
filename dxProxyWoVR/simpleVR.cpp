#include "simpleVR.h"
#include <algorithm>

simpleVR::simpleVR(bool showLogs) : printLogs(showLogs)
{
	InitalizeVR();
}

simpleVR::~simpleVR()
{
}

void simpleVR::InitalizeVR()
{
	float tIdentMat[4][4] = {
						{1, 0, 0, 0},
						{0, 1, 0, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 1}
	};

	//----
	// Sets a default identity matrix, and sets all other matrices to it
	//----
	memcpy(&identMatrix, tIdentMat, sizeof(uMatrix));
	memcpy(&projMatrixRaw[0], identMatrix._m, sizeof(uMatrix));
	memcpy(&projMatrixRaw[1], identMatrix._m, sizeof(uMatrix));
	memcpy(&eyeViewMatrixRaw[0], identMatrix._m, sizeof(uMatrix));
	memcpy(&eyeViewMatrixRaw[1], identMatrix._m, sizeof(uMatrix));
	memcpy(&eyeViewMatrix[0], identMatrix._m, sizeof(uMatrix));
	memcpy(&eyeViewMatrix[1], identMatrix._m, sizeof(uMatrix));
	memcpy(&hmdMatrix, identMatrix._m, sizeof(uMatrix));
	memcpy(&controllerMatrix[0], identMatrix._m, sizeof(uMatrix));
	memcpy(&controllerMatrix[1], identMatrix._m, sizeof(uMatrix));
	memcpy(&controllerMatrix[2], identMatrix._m, sizeof(uMatrix));
	memcpy(&controllerMatrix[3], identMatrix._m, sizeof(uMatrix));

	//layoutFinger[0] = fingerHandLayout();
	//layoutFinger[1] = fingerHandLayout();
}

bool simpleVR::PreloadVR()
{
	if (!vr::VR_IsHmdPresent())
	{
		//InitalizeVR();
		_isConnected = false;
		return _isConnected;
	}

	vr::EVRInitError eError = vr::VRInitError_None;
	vr::IVRSystem* localVRSession = vr::VR_Init(&eError, vr::VRApplication_Scene);

	//----
	// Gets the buffer and resolution sizes
	//----
	int32_t rX = 0;
	int32_t rY = 0;
	uint32_t rWidth = 0;
	uint32_t rHeight = 0;

	vr::IVRExtendedDisplay* d = vr::VRExtendedDisplay();
	d->GetWindowBounds(&rX, &rY, &rWidth, &rHeight);
	resolution.x = rWidth;
	resolution.y = rHeight;

	localVRSession->GetRecommendedRenderTargetSize(&rWidth, &rHeight);
	bufferSize.x = rWidth;
	bufferSize.y = rHeight;

	if (printLogs)
		logError << "Getting Buffers " << bufferSize.x << "x" << bufferSize.y << std::endl;

	vr::VR_Shutdown();
	localVRSession = nullptr;
}

void simpleVR::SetProjection(vr::HmdVector2_t depth)
{
	if (depthRange.v[0] != depth.v[0] || depthRange.v[1] != depth.v[1])
	{
		depthRange.v[0] = depth.v[0];
		depthRange.v[1] = depth.v[1];

		if (asymmetricProjection)
		{
			//----
			// Gets the left and right eye projection matricies
			//----
			vr::HmdMatrix44_t pMat[] = {
						openVRSession->GetProjectionMatrix(vr::Eye_Left, depthRange.v[0], depthRange.v[1]),
						openVRSession->GetProjectionMatrix(vr::Eye_Right, depthRange.v[0], depthRange.v[1])
			};

			float projView[][16] = {
				{
					pMat[0].m[0][0], pMat[0].m[1][0], pMat[0].m[2][0], pMat[0].m[3][0],
					pMat[0].m[0][1], pMat[0].m[1][1], pMat[0].m[2][1], pMat[0].m[3][1],
					pMat[0].m[0][2], pMat[0].m[1][2], pMat[0].m[2][2], pMat[0].m[3][2],
					pMat[0].m[0][3], pMat[0].m[1][3], pMat[0].m[2][3], pMat[0].m[3][3]
				},
				{
					pMat[1].m[0][0], pMat[1].m[1][0], pMat[1].m[2][0], pMat[1].m[3][0],
					pMat[1].m[0][1], pMat[1].m[1][1], pMat[1].m[2][1], pMat[1].m[3][1],
					pMat[1].m[0][2], pMat[1].m[1][2], pMat[1].m[2][2], pMat[1].m[3][2],
					pMat[1].m[0][3], pMat[1].m[1][3], pMat[1].m[2][3], pMat[1].m[3][3]
				}
			};

			//memcpy(&projMatrixRaw[0], &pMat[0], sizeof(float) * 4 * 4);
			//memcpy(&projMatrixRaw[1], &pMat[1], sizeof(float) * 4 * 4);
			memcpy(&projMatrixRaw[0], &projView[0], sizeof(float) * 4 * 4);
			memcpy(&projMatrixRaw[1], &projView[1], sizeof(float) * 4 * 4);

			textureBounds[0] = { 0.0f, 0.0f,  1.0f, 1.0f };
			textureBounds[1] = { 0.0f, 0.0f,  1.0f, 1.0f };
		}
		else
		{
			float lLeft = 0;
			float lRight = 0;
			float lTop = 0;
			float lBottom = 0;
			float rLeft = 0;
			float rRight = 0;
			float rTop = 0;
			float rBottom = 0;

			if (printLogs)
			{
				logError << "-- Getting Raw Projection" << std::endl;
			}
			openVRSession->GetProjectionRaw(vr::Eye_Left, &lLeft, &lRight, &lTop, &lBottom);
			openVRSession->GetProjectionRaw(vr::Eye_Right, &rLeft, &rRight, &rTop, &rBottom);

			float xList[4] = { -lLeft, lRight, -rLeft, rRight };
			float yList[4] = { -lTop, lBottom, -rTop, rBottom };
			float xTanHaflFOV = *std::max_element(xList, xList + 4);
			float yTanHaflFOV = *std::max_element(yList, yList + 4);

			if (printLogs)
			{
				logError << "-- Creating TextureBounds" << std::endl;
			}

			textureBounds[0].uMin = 0.5f + 0.5f * lLeft / xTanHaflFOV;
			textureBounds[0].uMax = 0.5f + 0.5f * lRight / xTanHaflFOV;
			textureBounds[0].vMin = 0.5f - 0.5f * lBottom / yTanHaflFOV;
			textureBounds[0].vMax = 0.5f - 0.5f * lTop / yTanHaflFOV;

			textureBounds[1].uMin = 0.5f + 0.5f * rLeft / xTanHaflFOV;
			textureBounds[1].uMax = 0.5f + 0.5f * rRight / xTanHaflFOV;
			textureBounds[1].vMin = 0.5f - 0.5f * rBottom / yTanHaflFOV;
			textureBounds[1].vMax = 0.5f - 0.5f * rTop / yTanHaflFOV;

			float Rad2Deg = 180.0f / (float)M_PI;
			float aspect = xTanHaflFOV / yTanHaflFOV;
			float oneOverDepth = 1 / (depthRange.v[1] - depthRange.v[0]);

			float h[4][4] = {
					{ 1, 0, 0, 0 },
					{ 0, 1, 0, 0 },
					{ 0, 0, 1, 0 },
					{ 0, 0, 0, 1 },
			};
			h[1][1] = 1 / yTanHaflFOV;
			h[0][0] = 1 * h[1][1] / aspect;
			h[2][2] = -(depthRange.v[1] * oneOverDepth);
			h[3][2] = (-depthRange.v[1] * depthRange.v[0]) * oneOverDepth;
			h[2][3] = -1;
			h[3][3] = 0;

			if (printLogs)
			{
				logError << "-- MatrixCreated" << std::endl;
			}

			memcpy(&projMatrixRaw[0], &h, sizeof(float) * 4 * 4);
			memcpy(&projMatrixRaw[1], &h, sizeof(float) * 4 * 4);
		}
	}
}

bool simpleVR::StartVR()
{
	if (!vr::VR_IsHmdPresent())
	{
		//InitalizeVR();
		_isConnected = false;
		return _isConnected;
	}
	
	if (_isConnected == false)
	{
		vr::EVRInitError eError = vr::VRInitError_None;
		openVRSession = vr::VR_Init(&eError, vr::VRApplication_Scene);
		openVRChaperone = vr::VRChaperone();
		openVRModels = (vr::IVRRenderModels*)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);
		vr::VRCompositor()->SetTrackingSpace(vr::TrackingUniverseSeated);

		textureBounds[0] = vr::VRTextureBounds_t();
		textureBounds[1] = vr::VRTextureBounds_t();
		SetProjection({ 0.06f, 1000.0f });

		
		vr::HmdMatrix34_t pView[] = {
					openVRSession->GetEyeToHeadTransform(vr::Eye_Left),
					openVRSession->GetEyeToHeadTransform(vr::Eye_Right)
		};

		//----
		// Gets the left and right eye offset view matricies
		//----
		float eyeView[][16] = {
			{
				pView[0].m[0][0], pView[0].m[1][0], pView[0].m[2][0], 0.0f,
				pView[0].m[0][1], pView[0].m[1][1], pView[0].m[2][1], 0.0f,
				pView[0].m[0][2], pView[0].m[1][2], pView[0].m[2][2], 0.0f,
				pView[0].m[0][3], pView[0].m[1][3], pView[0].m[2][3], 1.0f
			},
			{
				pView[1].m[0][0], pView[1].m[1][0], pView[1].m[2][0], 0.0f,
				pView[1].m[0][1], pView[1].m[1][1], pView[1].m[2][1], 0.0f,
				pView[1].m[0][2], pView[1].m[1][2], pView[1].m[2][2], 0.0f,
				pView[1].m[0][3], pView[1].m[1][3], pView[1].m[2][3], 1.0f
			}
		};

		memcpy(&eyeViewMatrixRaw[0], &eyeView[0], sizeof(uMatrix));
		memcpy(&eyeViewMatrixRaw[1], &eyeView[1], sizeof(uMatrix));

		memcpy(&eyeViewMatrix[0], &eyeViewMatrixRaw[0], sizeof(uMatrix));
		memcpy(&eyeViewMatrix[1], &eyeViewMatrixRaw[1], sizeof(uMatrix));


		
		if (asymmetricProjection)
		{
		}
		else
		{
			// Grow the recommended size to account for the overlapping fov
			bufferSize.x = (long)(bufferSize.x / std::fmax(textureBounds[0].uMax - textureBounds[0].uMin, textureBounds[1].uMax - textureBounds[1].uMin));
			bufferSize.y = (long)(bufferSize.y / std::fmax(textureBounds[0].vMax - textureBounds[0].vMin, textureBounds[1].vMax - textureBounds[1].vMin));
		}
		
		_isConnected = true;
	}

	Recenter();

	return _isConnected;
}

bool simpleVR::StopVR()
{
	if (_isConnected == true)
	{
		_isConnected = false;
		vr::VR_Shutdown();
		openVRSession = nullptr;

		return true;
	}
	else
	{
		return false;
	}
}

bool simpleVR::isEnabled()
{
	return _isConnected;
}

void simpleVR::Recenter()
{
	if (openVRSession && openVRChaperone)
		openVRChaperone->ResetZeroPose(vr::ETrackingUniverseOrigin::TrackingUniverseSeated);
}

POINT simpleVR::GetBufferSize()
{
	return bufferSize;
}

void simpleVR::SetFramePose()
{
	if (openVRSession && _isConnected)
	{
		static int lContNum = 0;
		static int rContNum = 0;

		vr::ETrackingUniverseOrigin universeOrigin = vr::VRCompositor()->GetTrackingSpace();
		//vr::VRCompositor()->WaitGetPoses(rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);
		vr::VRCompositor()->GetLastPoses(rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

		vr::TrackedDevicePose_t hmdPose = vr::TrackedDevicePose_t();
		vr::TrackedDevicePose_t controllerPose[2] = { 0, 0 };
		vr::TrackedDevicePose_t GenericTracker[3] = { 0, 0, 0 };
		int gTrackIndex = 0;

		//----
		// Loops though all (MaxDeviceCount(16)) available positions
		//----
		for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) {
			//----
			// Determines if there is a device connected to this index
			//----
			if (rTrackedDevicePose[i].bDeviceIsConnected) {
				//----
				// If there is a device connected, check and see if it is tracking and we have a valid pose
				//----
				if (rTrackedDevicePose[i].bPoseIsValid) {
					//----
					// Get the pose of the HMD itself
					//----
					vr::ETrackedDeviceClass classType = openVRSession->GetTrackedDeviceClass(i);
					if (classType == vr::TrackedDeviceClass_HMD) {
						hmdPose = rTrackedDevicePose[i];

						//----
						// Get the pose of the controllers
						//----
					}
					else if (classType == vr::TrackedDeviceClass_Controller) {
						//----
						// Check and see if we are dealing with the left or right controller
						//----
						//vr::VRControllerState_t controllerState;
						//openVRSession->GetControllerState(i, &controllerState, sizeof(vr::VRControllerState_t));

						vr::ETrackedControllerRole controllerRole = openVRSession->GetControllerRoleForTrackedDeviceIndex(i);
						if (controllerRole == vr::TrackedControllerRole_LeftHand) {
							controllerPose[0] = rTrackedDevicePose[i];
						}
						else if (controllerRole == vr::TrackedControllerRole_RightHand) {
							controllerPose[1] = rTrackedDevicePose[i];
						}
					}
					else if (classType == vr::TrackedDeviceClass_GenericTracker) {
						if (gTrackIndex < gTrackCount) {
							GenericTracker[gTrackIndex] = rTrackedDevicePose[i];
							gTrackIndex++;
						}
					}
				}
			}
		}

		vr::HmdMatrix34_t matPose;
		//----
		// Convert the HMD Pose into 4x4 Matrix
		//----
		if (hmdPose.bPoseIsValid) {
			matPose = hmdPose.mDeviceToAbsoluteTracking;
			float poseMatrix[4][4] = {
				matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0f,
				matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0f,
				matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0f,
				matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
			};
			memcpy(hmdMatrix.matrix, poseMatrix, sizeof(float) * 4 * 4);
		}
		else
		{
			memcpy(hmdMatrix.matrix, identMatrix.matrix, sizeof(float) * 4 * 4);
		}

		//----
		// Convert the Left Controller Pose into 4x4 Matrix
		//----
		if (controllerPose[0].bPoseIsValid) {
			matPose = controllerPose[0].mDeviceToAbsoluteTracking;
			float poseMatrix[] = {
				matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0f,
				matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0f,
				matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0f,
				matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
			};
			//memcpy(controllerLeftMatrix.matrix, poseMatrix, sizeof(float) * 4 * 4);
		}

		//----
		// Convert the Right Controller Pose into 4x4 Matrix
		//----
		if (controllerPose[1].bPoseIsValid) {
			matPose = controllerPose[1].mDeviceToAbsoluteTracking;
			float poseMatrix[] = {
				matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0f,
				matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0f,
				matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0f,
				matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
			};
			//memcpy(controllerRightMatrix.matrix, poseMatrix, sizeof(float) * 4 * 4);
		}
	}
}

void simpleVR::SetActionPose(vr::HmdMatrix34_t matPose, poseType poseType)
{
	float poseMatrix[] = {
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0f,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0f,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0f,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
	};
	if (poseType == poseType::LeftHand)
		memcpy(controllerMatrix[0].matrix, poseMatrix, sizeof(float) * 4 * 4);
	else if (poseType == poseType::LeftHandPalm)
		memcpy(controllerMatrix[1].matrix, poseMatrix, sizeof(float) * 4 * 4);
	else if (poseType == poseType::RightHand)
		memcpy(controllerMatrix[2].matrix, poseMatrix, sizeof(float) * 4 * 4);
	else if (poseType == poseType::RightHandPalm)
		memcpy(controllerMatrix[3].matrix, poseMatrix, sizeof(float) * 4 * 4);
}

void simpleVR::SetSkeletalPose(vr::VRBoneTransform_t* boneArray, int boneCount, poseType poseType)
{
	if (poseType == poseType::LeftHand && boneCount == 31)
	{
		for (int i = 0; i < boneCount; i++)
		{
			//layoutFinger[0].data[i].Translation = Vector4(boneArray[i].position.v[0], boneArray[i].position.v[1], boneArray[i].position.v[2], boneArray[i].position.v[3]);
			//layoutFinger[0].data[i].Rotation = Quat4(boneArray[i].orientation.w, boneArray[i].orientation.x, boneArray[i].orientation.y, boneArray[i].orientation.z);
			//layoutFinger[0].data[i].Scale = Vector4(1, 1, 1, 1);
		}
	}
	else if (poseType == poseType::RightHand && boneCount == 31)
	{
		for (int i = 0; i < boneCount; i++)
		{
			//layoutFinger[1].data[i].Translation = Vector4(boneArray[i].position.v[0], boneArray[i].position.v[1], boneArray[i].position.v[2], boneArray[i].position.v[3]);
			//layoutFinger[1].data[i].Rotation = Quat4(boneArray[i].orientation.w, boneArray[i].orientation.x, boneArray[i].orientation.y, boneArray[i].orientation.z);
			//layoutFinger[1].data[i].Scale = Vector4(1, 1, 1, 1);
		}
	}
}

uMatrix simpleVR::GetFramePose(poseType poseType, int eye)
{
	switch (poseType)
	{
	case poseType::Projection:
		return projMatrixRaw[eye];
		break;
	case poseType::EyeOffset:
		return eyeViewMatrix[eye];
		break;
	case poseType::hmdPosition:
		return hmdMatrix;
		break;
	case poseType::LeftHand:
		return controllerMatrix[0];
		break;
	case poseType::LeftHandPalm:
		return controllerMatrix[1];
		break;
	case poseType::RightHand:
		return controllerMatrix[2];
		break;
	case poseType::RightHandPalm:
		return controllerMatrix[3];
		break;
	default:
		return identMatrix;
		break;
	}
}
/*
fingerHandLayout simpleVR::GetSkeletalPose(poseType poseType)
{
	if (poseType == poseType::LeftHand)
		return layoutFinger[0];
	else if (poseType == poseType::RightHand)
		return layoutFinger[1];
}*/

void simpleVR::Render(ID3D11Texture2D* leftEye, ID3D11Texture2D* leftDepth, ID3D11Texture2D* rightEye, ID3D11Texture2D* rightDepth)
{
	if (openVRSession && _isConnected)
	{
		float colorA[] = { 0, 1, 0, 1 };

		vr::Texture_t completeTexture[] = {
					{ leftEye, vr::TextureType_DirectX, vr::ColorSpace_Gamma },
					{ rightEye, vr::TextureType_DirectX, vr::ColorSpace_Gamma },
		};

		/*
		typedef struct VRTextureWithDepth_t
		{
			void* handle; // void *
			enum ETextureType eType;
			enum EColorSpace eColorSpace;
			void* depth.handle; // void *
			struct HmdMatrix44_t depth.mProjection;
			struct HmdVector2_t depth.vRange;
		} VRTextureWithDepth_t;
		*/
		/*
		depthRange.v[0] = 0.0f;
		depthRange.v[1] = 1.0f;

		vr::HmdMatrix44_t projMat[2];
		projMat[0].m[0][0] = projMatrixRaw[0].matrix[0][0];
		projMat[0].m[0][1] = projMatrixRaw[0].matrix[1][0];
		projMat[0].m[0][2] = projMatrixRaw[0].matrix[2][0];
		projMat[0].m[0][3] = projMatrixRaw[0].matrix[3][0];

		projMat[0].m[1][0] = projMatrixRaw[0].matrix[0][1];
		projMat[0].m[1][1] = projMatrixRaw[0].matrix[1][1];
		projMat[0].m[1][2] = projMatrixRaw[0].matrix[2][1];
		projMat[0].m[1][3] = projMatrixRaw[0].matrix[3][1];

		projMat[0].m[2][0] = projMatrixRaw[0].matrix[0][2];
		projMat[0].m[2][1] = projMatrixRaw[0].matrix[1][2];
		projMat[0].m[2][2] = projMatrixRaw[0].matrix[2][2];
		projMat[0].m[2][3] = projMatrixRaw[0].matrix[3][2];

		projMat[0].m[3][0] = projMatrixRaw[0].matrix[0][3];
		projMat[0].m[3][1] = projMatrixRaw[0].matrix[1][3];
		projMat[0].m[3][2] = projMatrixRaw[0].matrix[2][3];
		projMat[0].m[3][3] = projMatrixRaw[0].matrix[3][3];


		projMat[1].m[0][0] = projMatrixRaw[1].matrix[0][0];
		projMat[1].m[0][1] = projMatrixRaw[1].matrix[1][0];
		projMat[1].m[0][2] = projMatrixRaw[1].matrix[2][0];
		projMat[1].m[0][3] = projMatrixRaw[1].matrix[3][0];

		projMat[1].m[1][0] = projMatrixRaw[1].matrix[0][1];
		projMat[1].m[1][1] = projMatrixRaw[1].matrix[1][1];
		projMat[1].m[1][2] = projMatrixRaw[1].matrix[2][1];
		projMat[1].m[1][3] = projMatrixRaw[1].matrix[3][1];

		projMat[1].m[2][0] = projMatrixRaw[1].matrix[0][2];
		projMat[1].m[2][1] = projMatrixRaw[1].matrix[1][2];
		projMat[1].m[2][2] = projMatrixRaw[1].matrix[2][2];
		projMat[1].m[2][3] = projMatrixRaw[1].matrix[3][2];

		projMat[1].m[3][0] = projMatrixRaw[1].matrix[0][3];
		projMat[1].m[3][1] = projMatrixRaw[1].matrix[1][3];
		projMat[1].m[3][2] = projMatrixRaw[1].matrix[2][3];
		projMat[1].m[3][3] = projMatrixRaw[1].matrix[3][3];

		vr::VRTextureWithDepth_t completeDepth[2];
		completeDepth[0].handle = leftEye;
		completeDepth[0].eType = vr::TextureType_DirectX;
		completeDepth[0].eColorSpace = vr::ColorSpace_Gamma;
		completeDepth[0].depth = { leftDepth, projMat[0], depthRange };

		completeDepth[1].handle = rightEye;
		completeDepth[1].eType = vr::TextureType_DirectX;
		completeDepth[1].eColorSpace = vr::ColorSpace_Gamma;
		completeDepth[1].depth = { rightDepth, projMat[1], depthRange };
		*/
		vr::VRTextureBounds_t _bound = { 0.0f, 0.0f,  1.0f, 1.0f };

		//textureBounds[0] = { 0.0f, 0.0f, 0.5f, 1.0f };
		//textureBounds[1] = { 0.5f, 0.0f, 1.0f, 1.0f };

		//WaitGetPoses();
		
		vr::EVRCompositorError error = vr::VRCompositorError_None;
		error = vr::VRCompositor()->Submit(vr::Eye_Left, &completeTexture[0], &textureBounds[0], vr::Submit_Default);
		//error = vr::VRCompositor()->Submit(vr::Eye_Left, &completeDepth[0], &textureBounds[0], vr::Submit_TextureWithDepth);
		if (error && printLogs) {
			logError << "SimpleVR VRCompositor Error: " << std::hex << error << std::endl;
		}

		error = vr::VRCompositor()->Submit(vr::Eye_Right, &completeTexture[1], &textureBounds[1], vr::Submit_Default);
		//error = vr::VRCompositor()->Submit(vr::Eye_Right, &completeDepth[1], &textureBounds[1], vr::Submit_TextureWithDepth);
		if (error && printLogs) {
			logError << "SimpleVR VRCompositor Error: " << std::hex << error << std::endl;
		}
		
		//WaitGetPoses();
	}
}

void simpleVR::WaitGetPoses()
{
	vr::VRCompositor()->WaitGetPoses(rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);
}

void simpleVR::MakeIPDOffset()
{
	memcpy(&eyeViewMatrix[0], &eyeViewMatrixRaw[0], sizeof(uMatrix));
	memcpy(&eyeViewMatrix[1], &eyeViewMatrixRaw[1], sizeof(uMatrix));

	//eyeViewMatrix[0]._m[12] += -(cfg->ipdOffset / 1000);
	//eyeViewMatrix[1]._m[12] += +(cfg->ipdOffset / 1000);
}

bool simpleVR::HasErrors()
{
	return ((logError.rdbuf()->in_avail() == 0) ? false : true);
}

std::string simpleVR::GetErrors()
{
	std::string curLog = logError.str();
	logError.str("");
	return curLog;
}
