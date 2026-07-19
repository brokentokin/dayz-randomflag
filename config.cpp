class CfgPatches
{
	class SoL_RandomFlag
	{
		units[] =
		{
			"SoL_RandomFlag"
		};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Camping"
		};
	};
};

class CfgMods
{
	class SoL_RandomFlag
	{
		dir = "RandomFlag";
		name = "Random Flag";
		author = "SoL";
		version = "1.0.0";
		type = "mod";
		dependencies[] =
		{
			"Game",
			"World",
			"Mission"
		};

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] =
				{
					"RandomFlag/Scripts/3_Game"
				};
			};

			class worldScriptModule
			{
				value = "";
				files[] =
				{
					"RandomFlag/Scripts/4_World"
				};
			};

			class missionScriptModule
			{
				value = "";
				files[] =
				{
					"RandomFlag/Scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Flag_White;

	class SoL_RandomFlag : Flag_White
	{
		scope = 2;
		displayName = "Folded Flag";
		descriptionShort = "A folded flag of unknown design. Open it to reveal the flag inside.";
		inventorySlot[] = {};
	};
};
