/*****************************/
// Roleplay Postion Loading    /
// Saves Players' Positions    /
// And re-loads them on spawn. /
// Made by EasSidezZ		   /
/*****************************/



#include <sourcemod>
#include <sdktools>
#include <morecolors>
#include <smlib>

#pragma semicolon 1

 

//Database
static String:SpawnPath[128];
static Float:PlayerPos[MAXPLAYERS + 1][3];


public Plugin:myinfo =
{
	name = "Roleplay Respawn - Main",
	author = "EasSidezZ",
	description = "Spawn",
	version = "1.0000.0",
	url = "sourcemod.net"
}

public OnMapStart()
{
	//Text File (Using Keyvalues)
	BuildPath(Path_SM, SpawnPath, 64, "data/roleplay/playerspawn.txt");
	
}

public OnClientPutInServer(Client)
{
	decl Handle:SavePos;
	decl Float:Origin[3];
	//decl String:Position[255];
	decl String:AuthId[44];
	decl Float:DefOrg[3];
	DefOrg[0] = 999.0;
	DefOrg[1] = 999.0;
	DefOrg[2] = 999.0;
	
	GetClientAuthString(Client, AuthId, sizeof(AuthId));
	
	SavePos = CreateKeyValues("Position");
	FileToKeyValues(SavePos, SpawnPath);
	KvJumpToKey(SavePos, "Origin", true);
	KvGetVector(SavePos, AuthId, Origin, DefOrg);
	PlayerPos[Client][0] = Origin[0];
	PlayerPos[Client][1] = Origin[1];
	PlayerPos[Client][2] = Origin[2];
	
	CreateTimer(3.5, TeleportClient, Client);
	
	CloseHandle(SavePos);
}

public Action:TeleportClient(Handle:timer, any:Client)
{
	if(IsPlayerAlive(Client) && IsClientConnected(Client) && IsClientInGame(Client))
	{
		TeleportEntity(Client, PlayerPos[Client], NULL_VECTOR, NULL_VECTOR);
	}
}
public OnClientDisconnect(Client)
{
	//Declare
	decl Handle:SavePos;
	decl Float:Origin[3];
	decl String:AuthId[44];
	
	//Get + Set
	if(IsClientInGame(Client) && IsPlayerAlive(Client))
	{	
		GetClientAbsOrigin(Client, Origin);
		GetClientAuthString(Client, AuthId, sizeof(AuthId));
		
		PlayerPos[Client][0] = Origin[0];
		PlayerPos[Client][1] = Origin[1];
		PlayerPos[Client][2] = Origin[2];
		
		//Create
		SavePos = CreateKeyValues("Position");
		FileToKeyValues(SavePos, SpawnPath);
		KvJumpToKey(SavePos, "Origin", true);
		KvSetVector(SavePos, AuthId, PlayerPos[Client]);
		KvRewind(SavePos);
		KeyValuesToFile(SavePos, SpawnPath);
	}
}
	
