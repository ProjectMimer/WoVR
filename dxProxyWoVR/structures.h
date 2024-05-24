#pragma once

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <algorithm>
#include <unordered_set>
#include "stCommon.h"

struct BoneNameLookup
{
	std::vector<std::pair<std::string, int>> boneNames; // string name, boneId
	std::map<int, std::vector<int>> boneLayout; // parent, direct children
	std::map<int, std::vector<int>> allChildren; // parent with all children
	std::vector<int> parentList; // parentId
	std::vector<int> keyBoneList; // keyBone
	int oldBoneOffset;

	BoneNameLookup()
	{
		boneNames = std::vector<std::pair<std::string, int>>();
		boneNames.push_back({ "ArmL", -1 });
		boneNames.push_back({ "ArmR", -1 });
		boneNames.push_back({ "ShoulderL", -1 });
		boneNames.push_back({ "ShoulderR", -1 });
		boneNames.push_back({ "SpineLow", -1 });
		boneNames.push_back({ "Waist", -1 });
		boneNames.push_back({ "Head", -1 });
		boneNames.push_back({ "Jaw", -1 });
		boneNames.push_back({ "IndexFingerR", -1 });
		boneNames.push_back({ "MiddleFingerR", -1 });
		boneNames.push_back({ "PinkyFingerR", -1 });
		boneNames.push_back({ "RingFingerR", -1 });
		boneNames.push_back({ "ThumbR", -1 });
		boneNames.push_back({ "IndexFingerL", -1 });
		boneNames.push_back({ "MiddleFingerL", -1 });
		boneNames.push_back({ "PinkyFingerL", -1 });
		boneNames.push_back({ "RingFingerL", -1 });
		boneNames.push_back({ "ThumbL", -1 });
		boneNames.push_back({ "$BTH", -1 });
		boneNames.push_back({ "$CSR", -1 });
		boneNames.push_back({ "$CSL", -1 });
		boneNames.push_back({ "_Breath", -1 });
		boneNames.push_back({ "_Name", -1 });
		boneNames.push_back({ "_NameMount", -1 });
		boneNames.push_back({ "$CHD", -1 });
		boneNames.push_back({ "$CCH", -1 });
		boneNames.push_back({ "Root", -1 });
		boneNames.push_back({ "Wheel1", -1 });
		boneNames.push_back({ "Wheel2", -1 });
		boneNames.push_back({ "Wheel3", -1 });
		boneNames.push_back({ "Wheel4", -1 });
		boneNames.push_back({ "Wheel5", -1 });
		boneNames.push_back({ "Wheel6", -1 });
		boneNames.push_back({ "Wheel7", -1 });
		boneNames.push_back({ "Wheel8", -1 });
		boneNames.push_back({ "HandL", -1 });
		boneNames.push_back({ "HandR", -1 });
		boneNames.push_back({ "ElbowL", -1 });
		boneNames.push_back({ "ElbowR", -1 });

		boneLayout = std::map<int, std::vector<int>>();
		allChildren = std::map<int, std::vector<int>>();
		parentList = std::vector<int>();
		keyBoneList = std::vector<int>();
		oldBoneOffset = 0;
	}

	std::string Get(int bone_index) {
		if (bone_index >= 0 && bone_index < (int)boneNames.size()) {
			return boneNames[bone_index].first;
		}
		else {
			return "_NA_";
		}
	}

	int Get(std::string name)
	{
		for (std::pair<std::string, int> item : boneNames)
			if (item.first == name)
				return item.second;
		return -1;
	}

	bool Set(int boneCount, int boneOffset)
	{
		if (oldBoneOffset != boneOffset)
		{
			oldBoneOffset = boneOffset;

			//----
			// Resets the bone ids and layout
			//----
			for (int i = 0; i < (int)boneNames.size(); i++)
				boneNames[i].second = -1;
			boneLayout = std::map<int, std::vector<int>>();
			allChildren = std::map<int, std::vector<int>>();
			parentList = std::vector<int>(boneCount);
			keyBoneList = std::vector<int>(boneCount);

			//----
			// Gets all the bones and the parent/child relationships
			//----
			for (int i = 0; i < boneCount; i++)
			{
				int keyBoneId = *(int*)(boneOffset + (i * 0x58) + 0x00);
				short parentBoneId = *(short*)(boneOffset + (i * 0x58) + 0x08);

				if (keyBoneId >= 0 && keyBoneId < (int)boneNames.size())
					boneNames[keyBoneId].second = i;
				
				parentList[i] = parentBoneId;
				keyBoneList[i] = keyBoneId;
				if (boneLayout.count(parentBoneId) == 0)
					boneLayout[parentBoneId] = std::vector<int>();
				if (boneLayout.count(i) == 0)
					boneLayout[i] = std::vector<int>();
				boneLayout[parentBoneId].push_back(i);
			}

			//----
			// Find the extra bones/offsets used for ik now
			//----
			int boneNameHandL = -1;
			for (int i = 0; i < (int)boneNames.size(); i++)
				if (boneNames[i].first == "HandL")
					boneNameHandL = i;

			int boneNameHandR = -1;
			for (int i = 0; i < (int)boneNames.size(); i++)
				if (boneNames[i].first == "HandR")
					boneNameHandR = i;

			int boneNameElbowL = -1;
			for (int i = 0; i < (int)boneNames.size(); i++)
				if (boneNames[i].first == "ElbowL")
					boneNameElbowL = i;

			int boneNameElbowR = -1;
			for (int i = 0; i < (int)boneNames.size(); i++)
				if (boneNames[i].first == "ElbowR")
					boneNameElbowR = i;


			int thumbL = boneLookup.Get("ThumbL");
			if (thumbL >= 0)
			{
				boneNames[boneNameHandL].second = boneLookup.parentList[thumbL];
				keyBoneList[boneNames[boneNameHandL].second] = boneNameHandL;
				if (boneNames[boneNameHandL].second >= 0)
				{
					boneNames[boneNameElbowL].second = boneLookup.parentList[boneNames[boneNameHandL].second];
					keyBoneList[boneNames[boneNameElbowL].second] = boneNameElbowL;
				}
			}

			int thumbR = boneLookup.Get("ThumbR");
			if (thumbR >= 0)
			{
				boneNames[boneNameHandR].second = boneLookup.parentList[thumbR];
				keyBoneList[boneNames[boneNameHandR].second] = boneNameHandR;
				if (boneNames[boneNameHandR].second >= 0)
				{
					boneNames[boneNameElbowR].second = boneLookup.parentList[boneNames[boneNameHandR].second];
					keyBoneList[boneNames[boneNameElbowR].second] = boneNameElbowR;
				}
			}

			UpdateChildren(-1);
			return true;
		}
		return false;
	}

	std::unordered_set<int> UpdateChildren(int index)
	{
		std::unordered_set<int> childList = std::unordered_set<int>();
		for (int childId : boneLayout[index])
		{
			childList.insert(childId);
			std::unordered_set<int> retList = UpdateChildren(childId);
			for (int retChild : retList)
				childList.insert(retChild);
		}

		allChildren[index].assign(childList.begin(), childList.end());
		std::sort(allChildren[index].begin(), allChildren[index].end());
		return childList;
	}

} boneLookup;

//----
// Used to pack the struct to the exact byte sizes
//----
#pragma pack(push, 1)

struct st20Container
{
	char unknown1[0x0150];					// 0x0000
	int ptr20;								// 0x0150
	char unknown2[0x001C];					// 0x0154
	int ptrSKIN;							// 0x0170
};

struct stModelContainer
{
	char unknown1[0x002C];					// 0x0000
	st20Container* p20Container;			// 0x002C
	char unknown2[0x0064];					// 0x0030
	int ptrBoneData;						// 0x0094
	int ptrBonePos;							// 0x0098
	char unknown3[0x0018];					// 0x009C
	uMatrix characterMatrix;				// 0x00B4
	uMatrix cameraMatrix;					// 0x00F4
	uMatrix Matrix3;						// 0x0174
};


struct stObjectData
{
	int unknown1;							// 0x0788, 0x0000
	int unknown2;
	int unknown3;
	int unknown4;
	Vector3 objPos;							// 0x0798, 0x0010
	float unknown5;							// 0x07A4, 0x001C
	float objRot;							// 0x07A8, 0x0020
	float objPitch;							// 0x07AC, 0x0024
	int unknown6;							// 0x07B0
	int unknown7;							// 0x07B4
	int Animation1;							// 0x07B8
	int Animation2;							// 0x07BC
	float unknown8;							// 0x07C0
	float unknown9;							// 0x07C4
	float unknown10;						// 0x07C8
	int MovementStatus;						// 0x07CC
	int unknown11;							// 0x07D0
	Vector3 objPos1;
	float objRot1;
	float objPitch1;
	int tickAtMovement;
	Vector3 forwardVectorX;					// 0x07EC
	Vector3 upVector;						// 0x07F8
	float unknown12;
	float unknown13;
	float unknown14;
	float unknown15;
	float curSpeed;							// 0x0814
	float walkSpeedForward;					// 0x0818
	float runSpeedForward;					// 0x081C
	float runSpeedBackward;					// 0x0820
	float swimSpeedForward;					// 0x0824
	float swimSpeedBackward;				// 0x0828
	float flySpeedForward;					// 0x082C
	float flySpeedBackward;					// 0x0830
};

struct stObjectManager
{
	char unknown0[0x0028];					// 0x0000
	stObjectManager* nextInLink;			// 0x0028
	int unknown1;							// 0x002C
	int objGuID;							// 0x0030
	int unknown2;							// 0x0034
	int unknown3;							// 0x0038
	stObjectManager* nextInLink1;			// 0x003C
	char unknown4[0x0058];					// 0x0040
	float scale1;							// 0x0098
	float scale2;							// 0x009C
	char unknown5[0x0014];					// 0x00A0
	stModelContainer* pModelContainer;		// 0x00B4
	char unknown6[0x10];					// 0x00B8
	byte alpha1;							// 0x00C8
	byte alpha2;							// 0x00C9
	byte alpha3;							// 0x00CA
	byte alpha4;							// 0x00CB
	char unknown7[0xC];						// 0x00CC
	stObjectData* ptrObjectData;			// 0x00D8
	char unknown8[0x06AC];					// 0x00DC
	stObjectData objectData;				// 0x0788
	char unknown9[0x018C];					// 0x0834
	int mount;								// 0x09C0
	char unknown10[0x644];					// 0x09C4
	int unknown11;							// 0x1008
	char unknown12[0xA58];					// 0x100C
	int modelID;							// 0x1A64
};
#pragma pack(pop)