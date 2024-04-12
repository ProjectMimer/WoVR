#pragma once
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <unordered_map>
#include <fstream>

struct characterFolder
{
    std::string path = "";
    std::string name = "";
    bool runUpdate = false;

    std::string getPath()
    {
        return path + name + "/";
    }

    void doUpdate()
    {
        runUpdate = true;
    }

    bool checkUpdate()
    {
        return runUpdate;
    }
};

struct characterInformation
{
    std::unordered_map<std::string, characterFolder> CharacterNames = std::unordered_map<std::string, characterFolder>();
    std::string path = "";
    std::string name = "";
    bool runUpdate = false;

    void Add(std::string characterName, std::string path)
    {
        CharacterNames[characterName] = characterFolder();
        CharacterNames[characterName].path = path;
        CharacterNames[characterName].name = characterName;
    }

    std::string getPath(std::string characterName = "")
    {
        if (characterName == "")
            return path + name + "/";
        else
        {
            if (CharacterNames.find(characterName) != CharacterNames.end())
                return CharacterNames[characterName].getPath();
            else
                return "";
        }
    }

    void doUpdate(std::string characterName = "")
    {
        if (characterName == "")
            runUpdate = true;
        else
        {
            if (CharacterNames.find(characterName) != CharacterNames.end())
                CharacterNames[characterName].doUpdate();
        }
    }

    bool checkUpdate()
    {
        for (std::unordered_map<std::string, characterFolder>::iterator it = CharacterNames.begin(); it != CharacterNames.end(); it++)
            runUpdate |= it->second.checkUpdate();
        return runUpdate;
    }
};

struct serverInformation
{
    std::unordered_map<std::string, characterInformation> ServerNames = std::unordered_map<std::string, characterInformation>();
    std::string path = "";
    std::string name = "";
    bool runUpdate = false;

    void Add(std::string serverName, std::string path)
    {
        ServerNames[serverName] = characterInformation();
        ServerNames[serverName].path = path;
        ServerNames[serverName].name = serverName;
    }

    void Add(std::string serverName, std::string characterName, std::string path)
    {
        if (ServerNames.find(serverName) != ServerNames.end())
            ServerNames[serverName].Add(characterName, path);
    }

    std::string getPath(std::string serverName = "", std::string characterName = "")
    {
        if (serverName == "")
            return path + name + "/";
        else
        {
            if (ServerNames.find(serverName) != ServerNames.end())
                return ServerNames[serverName].getPath(characterName);
            else
                return "";
        }
    }

    void doUpdate(std::string serverName = "", std::string characterName = "")
    {
        if (serverName == "")
            runUpdate = true;
        else
        {
            if (ServerNames.find(serverName) != ServerNames.end())
                ServerNames[serverName].doUpdate(characterName);
        }
    }

    bool checkUpdate()
    {
        for (std::unordered_map<std::string, characterInformation>::iterator it = ServerNames.begin(); it != ServerNames.end(); it++)
            runUpdate |= it->second.checkUpdate();
        return runUpdate;
    }
};

struct accountInformation
{
    std::unordered_map<std::string, serverInformation> AccountNames = std::unordered_map<std::string, serverInformation>();
    std::string path = "";
    bool runUpdate = false;

    void Add(std::string accountName, std::string path)
    {
        AccountNames[accountName] = serverInformation();
        AccountNames[accountName].path = path;
        AccountNames[accountName].name = accountName;
        path = path;
    }

    void Add(std::string accountName, std::string serverName, std::string path)
    {
        if (AccountNames.find(accountName) != AccountNames.end())
            AccountNames[accountName].Add(serverName, path);
    }

    void Add(std::string accountName, std::string serverName, std::string characterName, std::string path)
    {
        if (AccountNames.find(accountName) != AccountNames.end())
            AccountNames[accountName].Add(serverName, characterName, path);
    }

    std::string getPath(std::string accountName = "", std::string serverName = "", std::string characterName = "")
    {
        if (accountName == "")
            return path;
        else
        {
            if (AccountNames.find(accountName) != AccountNames.end())
                return AccountNames[accountName].getPath(serverName, characterName);
            else
                return "";
        }
    }

    void doUpdate(std::string accountName = "", std::string serverName = "", std::string characterName = "")
    {
        if (accountName == "")
            runUpdate = true;
        else
        {
            if (AccountNames.find(accountName) != AccountNames.end())
                AccountNames[accountName].doUpdate(serverName, characterName);
        }
    }

    bool checkUpdate()
    {
        for (std::unordered_map<std::string, serverInformation>::iterator it = AccountNames.begin(); it != AccountNames.end(); it++)
            runUpdate |= it->second.checkUpdate();
        return runUpdate;
    }
};


void CutupAddonFilesCopy(std::string g_VR_PATH, bool cfg_doCutUICopy);