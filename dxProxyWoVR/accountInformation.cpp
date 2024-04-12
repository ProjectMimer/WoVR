#include "accountInformation.h"
typedef std::vector<std::tuple<bool, std::string, std::string>> folderList;
#include <sstream>
extern std::stringstream logError;

folderList ListDirectory(std::string search_path, int fileTypes = 3)
{
    struct stat buffer;
    folderList fileList = folderList();
    WIN32_FIND_DATA file_data;

    if (stat(search_path.c_str(), &buffer) == 0)
    {
        HANDLE dir = FindFirstFile((search_path + "*").c_str(), &file_data);
        while (FindNextFile(dir, &file_data))
            if (strcmp(file_data.cFileName, ".") != 0 && strcmp(file_data.cFileName, "..") != 0)
                if (stat((search_path + file_data.cFileName).c_str(), &buffer) == 0)
                    // is it a directory and are we looking for directories?
                    if ((buffer.st_mode & S_IFDIR) && (fileTypes & 1))
                        fileList.push_back(std::tuple<bool, std::string, std::string>(true, search_path, file_data.cFileName));
                    // is it a readable file and are we looking for files?
                    else if ((buffer.st_mode & S_IFREG) && (fileTypes & 2))
                        fileList.push_back(std::tuple<bool, std::string, std::string>(false, search_path, file_data.cFileName));
    }
    return fileList;
}

void CopyFileToFrom(std::string toPath, std::string fromPath)
{
    struct stat buffer;
    if (stat(fromPath.c_str(), &buffer) == 0)
    {
        std::ifstream fromStream(fromPath, std::ios::binary);
        std::ofstream toStream(toPath, std::ios::binary);

        toStream << fromStream.rdbuf();

        toStream.close();
        fromStream.close();
    }
}

void CutupAddonFiles(std::string addonPathFrom, std::string itemPathTo)
{
    bool isDir;
    std::string path;
    std::string file;

    folderList fileList = ListDirectory(addonPathFrom, 2);
    for (folderList::iterator it = fileList.begin(); it != fileList.end(); it++)
    {
        std::tie(isDir, path, file) = *it;
        //logError << itemPathTo + file << " << " << path + file << std::endl;
        CopyFileToFrom(itemPathTo + file, path + file);
    }

    addonPathFrom += "SavedVariables/";
    itemPathTo += "SavedVariables/";

    fileList = ListDirectory(addonPathFrom, 2);
    for (folderList::iterator it = fileList.begin(); it != fileList.end(); it++)
    {
        std::tie(isDir, path, file) = *it;
        //logError << itemPathTo + file << " << " << path + file << std::endl;
        CopyFileToFrom(itemPathTo + file, path + file);
    }
}

void CutupAddonModify(std::string accountFullPath, std::vector<std::string> charServerList)
{
    struct stat buffer;

    std::vector<std::string> updateFileList = {
        accountFullPath + "SavedVariables/Omen.lua",
        accountFullPath + "SavedVariables/Recount.lua",
        accountFullPath + "SavedVariables/SatrinaBuffFrame.lua"
    };
    
    for (std::string updateFile : updateFileList)
    {
        if (stat(updateFile.c_str(), &buffer) == 0)
        {
            std::string fileData;
            std::ifstream fileInput(updateFile);

            fileInput.seekg(0, std::ios::end);
            fileData.reserve(fileInput.tellg());
            fileInput.seekg(0, std::ios::beg);

            fileData.assign((std::istreambuf_iterator<char>(fileInput)),
                             std::istreambuf_iterator<char>());
            fileInput.close();

            //----
            // Look for the profileKeys tag
            //----
            std::size_t profileKeysPos = fileData.find("[\"profileKeys\"]");
            std::size_t profileKeysOpen = std::string::npos;
            std::size_t profileKeysClose = std::string::npos;

            if (profileKeysPos != std::string::npos)
            {
                profileKeysPos += std::string("[\"profileKeys\"]").length();

                //----
                // Search for the profileKeys { } brackets
                //----
                profileKeysOpen = fileData.find("{", profileKeysPos);
                profileKeysClose = fileData.find("}", profileKeysPos);
                if (profileKeysOpen != std::string::npos && profileKeysClose != std::string::npos)
                {
                    std::string newData = fileData.substr(profileKeysOpen, profileKeysClose + 1 - profileKeysOpen);

                    //----
                    // Copy the beginning and end of the file around profileKeys
                    //----
                    std::string fileBegin = fileData.substr(0, profileKeysOpen);
                    std::string fileEnd = fileData.substr(profileKeysClose + 1);

                    //----
                    // Add the character server names
                    //----
                    std::string charList = "{\n";
                    for (std::string charServerLine : charServerList)
                        charList += "\t\t" + charServerLine + "\n";
                    charList += "\t}";

                    //----
                    // Output the full new file
                    //----
                    std::ofstream fileOutput(updateFile);
                    fileOutput << fileBegin << charList << fileEnd;
                    fileOutput.close();
                }
            }
        }
    }
}


void CutupAddonFilesCopy(std::string g_VR_PATH, bool cfg_doCutUICopy)
{
    accountInformation accInfo = accountInformation();

    struct stat buffer;
    std::string addonPathFrom = g_VR_PATH + "_files_/";
    if (stat(addonPathFrom.c_str(), &buffer) == 0 && cfg_doCutUICopy)
    {
        bool isDir;
        std::string path;

        std::string addonDataPath = "./WTF/Account/";
        std::string curAccount = "";
        std::string curServer = "";
        std::string curChar = "";

        std::vector<std::string> charServerList = std::vector<std::string>();

        //----
        // Find and loop through the account folder
        //----
        folderList accountList = ListDirectory(addonDataPath, 1);
        for (folderList::iterator itAccount = accountList.begin(); itAccount != accountList.end(); itAccount++)
        {
            std::tie(isDir, path, curAccount) = *itAccount;
            accInfo.Add(curAccount, path);

            std::string accDir = accInfo.getPath(curAccount);
            if (stat((accDir + "patch_id.dat").c_str(), &buffer) != 0)
                accInfo.doUpdate(curAccount);

            //----
            // Find and loop through the server folders
            //----
            folderList serverList = ListDirectory(path + curAccount + "/", 1);
            for (folderList::iterator itServer = serverList.begin(); itServer != serverList.end(); itServer++)
            {
                std::tie(isDir, path, curServer) = *itServer;
                if (curServer != "SavedVariables")
                {
                    accInfo.Add(curAccount, curServer, path);

                    //----
                    // Find and loop through the character folders
                    //----
                    folderList characterList = ListDirectory(path + curServer + "/", 1);
                    for (folderList::iterator itCharacter = characterList.begin(); itCharacter != characterList.end(); itCharacter++)
                    {
                        std::tie(isDir, path, curChar) = *itCharacter;
                        accInfo.Add(curAccount, curServer, curChar, path);

                        charServerList.push_back("[\"" + curChar + " - " + curServer + "\"] = \"VR\",");

                        std::string charDir = accInfo.getPath(curAccount, curServer, curChar);
                        if (stat((charDir + "patch_id.dat").c_str(), &buffer) != 0)
                            accInfo.doUpdate(curAccount, curServer, curChar);
                    }
                }
            }
        }

        for (std::pair<std::string, serverInformation> accountItem : accInfo.AccountNames)
        {
            std::string accountFullPath = accInfo.getPath(accountItem.first);

            std::vector<std::string> readOnlyList = {
                    accountFullPath + "SavedVariables/Omen.lua",
                    accountFullPath + "SavedVariables/Omen.lua.bak",
                    accountFullPath + "SavedVariables/Recount.lua",
                    accountFullPath + "SavedVariables/Recount.lua.bak",
                    accountFullPath + "SavedVariables/SatrinaBuffFrame.lua",
                    accountFullPath + "SavedVariables/SatrinaBuffFrame.lua.bak",
            };
            //----
            // IS THIS BROKEN?? ^^^^
            //----

            //----
            // unset omen and recount readonly property if they exist
            //----
            for (std::string readOnly : readOnlyList)
                if (stat(readOnly.c_str(), &buffer) == 0)
                    SetFileAttributesA(readOnly.c_str(), GetFileAttributesA(readOnly.c_str()) & ~FILE_ATTRIBUTE_READONLY);

            if (accountItem.second.runUpdate)
                CutupAddonFiles(addonPathFrom, accountFullPath);
            CutupAddonModify(accountFullPath, charServerList);

            //----
            // Set omen and recount to readonly
            //----
            for (std::string readOnly : readOnlyList)
                if (stat(readOnly.c_str(), &buffer) == 0)
                    SetFileAttributesA(readOnly.c_str(), FILE_ATTRIBUTE_READONLY);

            for (std::pair<std::string, characterInformation> serverItem : accountItem.second.ServerNames)
            {
                for (std::pair<std::string, characterFolder> characterItem : serverItem.second.CharacterNames)
                {
                    if (characterItem.second.runUpdate)
                    {
                        std::string charFullPath = accInfo.getPath(accountItem.first, serverItem.first, characterItem.first);
                        std::string chatPath = charFullPath + "chat-cache.txt";
                        
                        //----
                        // unset chat-cache.txt readonly property if it exist
                        //----
                        if (stat(chatPath.c_str(), &buffer) == 0)    SetFileAttributesA(chatPath.c_str(), GetFileAttributesA(chatPath.c_str()) & ~FILE_ATTRIBUTE_READONLY);

                        CutupAddonFiles(addonPathFrom + "(SERVER_NAME)/(CHARACTER_NAME)/", charFullPath);

                        //----
                        // Set chat-cache.txt to readonly
                        //----
                        SetFileAttributesA(chatPath.c_str(), FILE_ATTRIBUTE_READONLY);
                    }
                }
            }
        }
    }
}
