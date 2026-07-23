class CfgPatches
{
	class Tokin_RandomFlag
	{
		units[] =
		{
			"Tokin_RandomFlag",
			"Tokin_HeyBarmbyFlag",
			"Armband_Tokin_HeyBarmby"
		};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Characters_Tops",
			"DZ_Gear_Camping"
		};
	};
};

class CfgMods
{
	class Tokin_RandomFlag
	{
		dir = "RandomFlag";
		name = "HBC Random Flag";
		author = "Tokin";
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
	class Armband_ColorBase;

	class Tokin_RandomFlag : Flag_White
	{
		scope = 2;
		displayName = "Folded Flag";
		descriptionShort = "A folded flag of unknown design. Open it to reveal the flag inside.";
		inventorySlot[] = {};
		hiddenSelectionsTextures[] =
		{
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa"
		};
	};

	class Tokin_HeyBarmbyFlag : Flag_White
	{
		scope = 2;
		displayName = "HeyBarmby Flag";
		descriptionShort = "A flag featuring HeyBarmby.";
		color = "Tokin_HeyBarmby";
		hiddenSelectionsTextures[] =
		{
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa"
		};
	};

	class Armband_Tokin_HeyBarmby : Armband_ColorBase
	{
		scope = 2;
		displayName = "HeyBarmby Armband";
		descriptionShort = "An armband featuring HeyBarmby, cut from a matching flag.";
		visibilityModifier = 0.95;
		color = "Tokin_HeyBarmby";
		hiddenSelectionsTextures[] =
		{
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa",
			"RandomFlag\Data\Textures\heybarmby_randomflag_co.paa"
		};
	};
};
