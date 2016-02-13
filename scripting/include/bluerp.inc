//BlueRP Stock v1 by EasSidezZ
stock IsValidClient(client, bool:replaycheck = true)
{
    if(client <= 0 || client > MaxClients)
    {
        return false;
    }
    if(!IsClientInGame(client))
    {
        return false;
    }
    if(GetEntProp(client, Prop_Send, "m_bIsCoaching"))
    {
        return false;
    }
    if(replaycheck)
    {
        if(IsClientSourceTV(client) || IsClientReplay(client)) return false;
    }
    return true;
}  

/**
 * Sends a Dialog Menu to a client
 *
 * @param Level			Hud Type
 * @param Time			Hud Time
 * @param r			Red
 * @param g			Green
 * @param b			Blue
 * @param a			Alpha
 * @param Text			Message
 * @return			No bool.
 */
stock PrintEscapeText(Client, String:sBuffer[], any:...)
{
	new String:sMessage[1028];
	VFormat(sMessage, sizeof(sMessage), sBuffer, 3);
	new Handle:hKV = CreateKeyValues("message", "title", sMessage);
	KvSetColor(hKV, "color", 250, 250, 250, 250);
	KvSetNum(hKV, "level", 0);
	KvSetNum(hKV, "time", 60);
	CreateDialog(Client, hKV, DialogType_Menu);
	CreateDialog(Client, hKV, DialogType_Entry);
	CreateDialog(Client, hKV, DialogType_Text);
	CloseHandle(hKV);
}

/*
 * Set's a clients speed
 * @param Client Player to use
 * @param Speed Speed to use
 */
stock SetSpeed(Client, Float:fSpeed)
{
	new oSpeedOffset = FindSendPropOffs("CHL2MP_Player", "m_flMaxspeed");
	if(oSpeedOffset > 0) SetEntData(Client, oSpeedOffset, fSpeed, 4, true);
}

/*
 * Saves an integer
 * @param Vault Handle to the text file
 * @param Key The keyvalue name to use
 * @param SteamId The authid of the client
 * @param Variable Integer to store
 */
stock SaveInteger(Handle:hVault, const String:sKey[], const String:sSaveKey[], iVariable)
{
	if(Variable <= 0)
	{
		KvJumpToKey(hVault, sKey, false);
		KvDeleteKey(hVault, sSaveKey);
		KvRewind(hVault);
	}
	else
	{
		KvJumpToKey(hVault, sKey, true);
		KvSetNum(hVault, sSaveKey, iVariable);
		KvRewind(hVault);
	}
}

/*
 * Saves a string
 * @param Vault Handle to the text file
 * @param Key The keyvalue name to use
 * @param SteamId The authid of the client
 * @param Variable String to store
 */
stock SaveString(Handle:hVault, const String:sKey[], const String:sSaveKey[], const String:sVariable[])
{
	KvJumpToKey(hVault, sKey, true);
	KvSetString(hVault, sSaveKey, sVariable);
	KvRewind(hVault);
}

/*
 * Saves a string
 * @param Vault Handle to the text file
 * @param Key The keyvalue name to use
 * @param SteamId The authid of the client
 * @param Variable String to store
 */
stock SaveString2(Handle:hVault, const String:sKey[64], const String:sSaveKey[255], const String:sVariable[255])
{
	KvJumpToKey(hVault, sKey, true);
	KvSetString(hVault, sSaveKey, sVariable);
	KvRewind(hVault);
}

/*
 * Loads an integer
 * @param Vault Handle to the text file
 * @param Key The keyvalue name to use
 * @param SteamId The authid of the client
 * @param DefaultValue Integer to return if key not found
 */ 
stock LoadInteger(Handle:hVault, const String:sKey[], const String:sSaveKey[], iDefaultValue)
{
	KvJumpToKey(hVault, sKey, false);
	new iVariable = KvGetNum(hVault, sSaveKey, iDefaultValue);
	KvRewind(hVault);
	return iVariable;
}

/*
 * Loads an integer
 * @param Vault Handle to the text file
 * @param Key The keyvalue name to use
 * @param SteamId The authid of the client
 * @param DefaultValue Integer to return if key not found
 */
stock LoadInteger2(Handle:hVault, const String:sKey[255], const String:sSaveKey[255], iDefaultValue)
{
	KvJumpToKey(hVault, sKey, false);
	new iVariable = KvGetNum(hVault, sSaveKey, iDefaultValue);
	KvRewind(hVault);
	return iVariable;
}

/*
 * Loads a string
 * @param Vault Handle to the text file
 * @param Key The keyvalue name to use
 * @param SteamId The authid of the client
 * @param DefaultValue String to return if key not found
 * @param Reference String to return through reference
 */
stock LoadString(Handle:hVault, const String:sKey[], const String:sSaveKey[], const String:sDefaultValue[], String:sReference[])
{
	KvJumpToKey(hVault, sKey, false);
	KvGetString(hVault, sSaveKey, sReference, 255, sDefaultValue);
	KvRewind(hVault);
}

stock LoadString2(Handle:hVault, const String:sKey[255], const String:sSaveKey[255], const String:sDefaultValue[255], String:sReference[255])
{
	KvJumpToKey(hVault, sKey, false);
	KvGetString(hVault, sSaveKey, sReference, 255, sDefaultValue);
	KvRewind(hVault);
}

stock LoadString3(Handle:hVault, const String:sKey[255], const String:sSaveKey[255], const String:sDefaultValue[255], String:sReference[1000])
{
	KvJumpToKey(hVault, sKey, false);
	KvGetString(hVault, sSaveKey, sReference, 255, sDefaultValue);
	KvRewind(hVault);
}

/*
 * Prints NPC info
 * @param Client Player to print to
 * @param Vault Keyvalue handle to use
 * @param Header Header to use
 * @param Key Subkey to find inside the vault
 * @param MaxNPCs Maximum number of NPCs
 */
stock PrintNPC(Client, Handle:hVault, const String:sHeader[255], const String:sKey[32], iMaxNPCs)
{
	//Declare:
	decl String:sNPC[255], String:sData[255];

	//Print:
	PrintToConsole(Client, sHeader);
	for(new X = 0; X < iMaxNPCs; X++)
	{

		//Convert:
		IntToString(X, sNPC, 255);
	
		//Load:
		LoadString(hVault, sKey, sNPC, "Null", sData);

		//Found in DB:
		if(StrContains(sData, "Null", false) == -1) PrintToConsole(Client, "--%s: %s", sNPC, sData);	
	}
}

/*
 * Prints job info
 * @param Client Player to print to
 * @param Vault Keyvalue handle to use
 * @param Header Header to use
 * @param Key Subkey to find inside the vault
 * @param MaxNPCs Maximum number of Jobs
 */
stock PrintJob(Client, Handle:Vault, const String:Header[255], const String:Key[32], MaxJobs)
{

	//Declare:
	decl String:JobId[255], String:JobTitle[255];

	//Print:
	PrintToConsole(Client, Header);
	for(new X = 0; X < MaxJobs; X++)
	{

		//Convert:
		IntToString(X, JobId, 255);
	
		//Load:
		LoadString(Vault, Key, JobId, "Null", JobTitle);

		//Found in DB:
		if(StrContains(JobTitle, "Null", false) == -1) PrintToConsole(Client, "--%s: %s", JobId, JobTitle);	
	}
}


/**
 * Adds an informational string to the server's public "tags".
 * This string should be a short, unique identifier.
 *
 *
 * @param tag            Tag string to append.
 * @noreturn
 */
stock AddServerTag2(const String:tag[])
{
    new Handle:hTags = INVALID_HANDLE;
    hTags = FindConVar("sv_tags");
    if(hTags != INVALID_HANDLE)
    {
        decl String:tags[256];
        GetConVarString(hTags, tags, sizeof(tags));
        if(StrContains(tags, tag, true) > 0) return;
        if(strlen(tags) == 0)
        {
            Format(tags, sizeof(tags), tag);
        }
        else
        {
            Format(tags, sizeof(tags), "%s,%s", tags, tag);
        }
        SetConVarString(hTags, tags, true);
    }
}

/**
 * Removes a tag previously added by the calling plugin.
 *
 * @param tag            Tag string to remove.
 * @noreturn
 */
stock RemoveServerTag2(const String:tag[])
{
    new Handle:hTags = INVALID_HANDLE;
    hTags = FindConVar("sv_tags");
    if(hTags != INVALID_HANDLE)
    {
        decl String:tags[50]; //max size of sv_tags cvar
        GetConVarString(hTags, tags, sizeof(tags));
        if(StrEqual(tags, tag, true))
        {
            Format(tags, sizeof(tags), "");
            SetConVarString(hTags, tags, true);
            return;
        }
        new pos = StrContains(tags, tag, true);
        new len = strlen(tags);
        if(len > 0 && pos > -1)
        {
            new bool:found;
            new String:taglist[50][50];
            ExplodeString(tags, ",", taglist, sizeof(taglist[]), sizeof(taglist));
            for(new i;i < sizeof(taglist[]);i++)
            {
                if(StrEqual(taglist[i], tag, true))
                {
                    Format(taglist[i], sizeof(taglist), "");
                    found = true;
                    break;
                }
            }    
            if(!found) return;
            ImplodeStrings(taglist, sizeof(taglist[]), ",", tags, sizeof(tags));
            if(pos == 0)
            {
                tags[0] = 0x20;
            }    
            else if(pos == len-1)
            {
                Format(tags[strlen(tags)-1], sizeof(tags), "");
            }    
            else
            {
                ReplaceString(tags, sizeof(tags), ",,", ",");
            }    
            SetConVarString(hTags, tags, true);
        }
    }    
}  

stock bool:IntToBool(iValue)
{
	switch(iValue)
	{
		case 0: return false;

		case 1: return true;

		default: return false;
	}

	return false;
}

stock BoolToInt(bool:bBool)
{
	return (bBool) ? 1 : 0;
}

stock GetEntityDistance(iEnt, iEnt2)
{
	if(IsValidEntity(iEnt) && IsValidEntity(iEnt2))
	{
		decl Float:fEntOrigin[3], Float:fEnt2Origin[3];

		GetEntPropVector(iEnt, Prop_Send, "m_vecOrigin", fEntOrigin);
		GetEntPropVector(iEnt2, Prop_Send, "m_vecOrigin", fEnt2Origin);

		new Float:iDistance = GetVectorDistance(fEntOrigin, fEnt2Origin);

		return RoundToCeil(iDistance);
	}

	return 0;
}

/**
 * Checks if a string contains a vowel
 * This string should be a short, unique identifier.
 *
 *
 * @param sString            String to append.
 * @return true if contains, false if not
 */
 stock bool:StrHasVowel(const String:sString[])
 {
	new String:sVowels[][] = { "a", "e", "i", "o", "u" }
	if(strlen(sString) == 0)
	{
		return false;
	}
	
	for(new i = 0; i < 5; i++)
	{
		if(StrContains(sString, sVowels[i], false) == 0)
		{
			return true;
		}
		else return false;
	}
	
	return false;
}

/**
 * Causes a Client's screen to shake violently
 * This is meant to give seizures probably
 *
 *
 * @param sClient           Client Index.
 * @param fLength			How long to attempt seizures
 * @param fSeverity			How severe the fucking seizure should be
 * @return 					No return
 */
stock Shake(Client, Float:fLength, Float:fSeverity)
{
	if(IsClientInGame(Client))
	{		
		new UserMsg:iShakeID = GetUserMessageId("Shake");
		new SendClient[2];
		SendClient[0] = Client;
		
		new Handle:hViewMessage = StartMessageEx(iShakeID, SendClient, 1);
		BfWriteByte(hViewMessage, 0);
		BfWriteFloat(hViewMessage, fSeverity);
		BfWriteFloat(hViewMessage, 10.0);
		BfWriteFloat(hViewMessage, fLength);	
		EndMessage();
	}
}