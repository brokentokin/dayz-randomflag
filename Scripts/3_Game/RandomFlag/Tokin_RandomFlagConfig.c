class Tokin_RandomFlagEntry
{
	string ClassName;
	float Weight;

	void Tokin_RandomFlagEntry(string class_name = "", float weight = 1.0)
	{
		ClassName = class_name;
		Weight = weight;
	}
}

class Tokin_RandomFlagConfig
{
	int Version;
	float OpenActionSeconds;
	ref array<ref Tokin_RandomFlagEntry> Flags;

	void Tokin_RandomFlagConfig()
	{
		Version = 1;
		OpenActionSeconds = 2.0;
		Flags = new array<ref Tokin_RandomFlagEntry>;
	}
}

class Tokin_RandomFlagConfigManager
{
	static const string CONFIG_DIRECTORY = "$profile:Tokin";
	static const string CONFIG_PATH = "$profile:Tokin/RandomFlagConfig.json";
	static const float DEFAULT_OPEN_ACTION_SECONDS = 2.0;
	static const float MINIMUM_OPEN_ACTION_SECONDS = 1.0;

	protected static ref Tokin_RandomFlagConfig s_Config;
	protected static ref array<ref Tokin_RandomFlagEntry> s_ValidFlags;
	protected static bool s_LoadAttempted;

	static void Load()
	{
		if (!GetGame() || !GetGame().IsServer())
			return;

		s_LoadAttempted = true;
		s_ValidFlags = new array<ref Tokin_RandomFlagEntry>;

		MakeDirectory(CONFIG_DIRECTORY);

		if (!FileExist(CONFIG_PATH))
		{
			s_Config = CreateDefaultConfig();
			SaveDefaultConfig();
		}
		else
		{
			s_Config = new Tokin_RandomFlagConfig();

			string load_error;
			if (!JsonFileLoader<Tokin_RandomFlagConfig>.LoadFile(CONFIG_PATH, s_Config, load_error))
			{
				ErrorEx("[Random Flag] " + load_error);
				ErrorEx("[Random Flag] Configuration was not loaded. Folded Flags will not be consumed.");
				return;
			}
		}

		ValidateOpenActionSeconds();
		BuildValidFlagPool();

		Print("[Random Flag] Loaded " + s_ValidFlags.Count() + " valid flag entries from " + CONFIG_PATH + ".");
	}

	static float GetOpenActionSeconds()
	{
		if (!s_LoadAttempted)
			Load();

		if (!s_Config)
			return DEFAULT_OPEN_ACTION_SECONDS;

		if (s_Config.OpenActionSeconds < MINIMUM_OPEN_ACTION_SECONDS)
			return MINIMUM_OPEN_ACTION_SECONDS;

		return s_Config.OpenActionSeconds;
	}

	static string GetRandomFlagClassName()
	{
		if (!s_LoadAttempted)
			Load();

		if (!s_ValidFlags || s_ValidFlags.Count() == 0)
		{
			ErrorEx("[Random Flag] No valid, positively weighted flag entries are available.");
			return "";
		}

		float total_weight = 0.0;
		foreach (Tokin_RandomFlagEntry weighted_flag : s_ValidFlags)
		{
			total_weight += weighted_flag.Weight;
		}

		float roll = Math.RandomFloat(0.0, total_weight);
		float cumulative_weight = 0.0;

		foreach (Tokin_RandomFlagEntry candidate : s_ValidFlags)
		{
			cumulative_weight += candidate.Weight;
			if (roll < cumulative_weight)
				return candidate.ClassName;
		}

		// Floating-point safety fallback. This should only be reachable if the
		// random value lands on the upper boundary because of engine rounding.
		return s_ValidFlags.Get(s_ValidFlags.Count() - 1).ClassName;
	}

	protected static void BuildValidFlagPool()
	{
		if (!s_Config || !s_Config.Flags)
		{
			ErrorEx("[Random Flag] The configuration has no Flags array.");
			return;
		}

		foreach (Tokin_RandomFlagEntry flag_entry : s_Config.Flags)
		{
			if (!flag_entry)
			{
				ErrorEx("[Random Flag] Ignoring a null entry in Flags.");
				continue;
			}

			if (flag_entry.ClassName == "")
			{
				ErrorEx("[Random Flag] Ignoring an entry with an empty ClassName.");
				continue;
			}

			if (flag_entry.Weight <= 0.0)
			{
				ErrorEx("[Random Flag] Ignoring " + flag_entry.ClassName + " because Weight must be greater than zero.");
				continue;
			}

			if (!ClassExists(flag_entry.ClassName))
			{
				ErrorEx("[Random Flag] Ignoring missing classname " + flag_entry.ClassName + ". Check that its providing mod is loaded.");
				continue;
			}

			s_ValidFlags.Insert(flag_entry);
		}
	}

	protected static void ValidateOpenActionSeconds()
	{
		if (!s_Config)
			return;

		if (s_Config.OpenActionSeconds < MINIMUM_OPEN_ACTION_SECONDS)
		{
			ErrorEx("[Random Flag] OpenActionSeconds cannot be less than 1 second. Using the minimum of 1 second.");
			s_Config.OpenActionSeconds = MINIMUM_OPEN_ACTION_SECONDS;
		}
	}

	protected static bool ClassExists(string class_name)
	{
		if (GetGame().ConfigIsExisting("CfgVehicles " + class_name))
			return true;

		if (GetGame().ConfigIsExisting("CfgWeapons " + class_name))
			return true;

		if (GetGame().ConfigIsExisting("CfgMagazines " + class_name))
			return true;

		return false;
	}

	protected static void SaveDefaultConfig()
	{
		string save_error;
		if (!JsonFileLoader<Tokin_RandomFlagConfig>.SaveFile(CONFIG_PATH, s_Config, save_error))
		{
			ErrorEx("[Random Flag] " + save_error);
			ErrorEx("[Random Flag] The in-memory defaults will remain active for this server session.");
			return;
		}

		Print("[Random Flag] Created default configuration at " + CONFIG_PATH + ".");
	}

	protected static Tokin_RandomFlagConfig CreateDefaultConfig()
	{
		Tokin_RandomFlagConfig config = new Tokin_RandomFlagConfig();

		AddDefaultFlag(config, "Flag_APA");
		AddDefaultFlag(config, "Flag_Altis");
		AddDefaultFlag(config, "Flag_BabyDeer");
		AddDefaultFlag(config, "Flag_Bear");
		AddDefaultFlag(config, "Flag_Bohemia");
		AddDefaultFlag(config, "Flag_BrainZ");
		AddDefaultFlag(config, "Flag_CDF");
		AddDefaultFlag(config, "Flag_CHEL");
		AddDefaultFlag(config, "Flag_CMC");
		AddDefaultFlag(config, "Flag_Cannibals");
		AddDefaultFlag(config, "Flag_Chedaki");
		AddDefaultFlag(config, "Flag_Chernarus");
		AddDefaultFlag(config, "Flag_Crook");
		AddDefaultFlag(config, "Flag_DayZ");
		AddDefaultFlag(config, "Flag_HunterZ");
		AddDefaultFlag(config, "Flag_Livonia");
		AddDefaultFlag(config, "Flag_LivoniaArmy");
		AddDefaultFlag(config, "Flag_LivoniaPolice");
		AddDefaultFlag(config, "Flag_NAPA");
		AddDefaultFlag(config, "Flag_NSahrani");
		AddDefaultFlag(config, "Flag_Pirates");
		AddDefaultFlag(config, "Flag_RSTA");
		AddDefaultFlag(config, "Flag_Refuge");
		AddDefaultFlag(config, "Flag_Rex");
		AddDefaultFlag(config, "Flag_Rooster");
		AddDefaultFlag(config, "Flag_SSahrani");
		AddDefaultFlag(config, "Flag_Sakhal");
		AddDefaultFlag(config, "Flag_Snake");
		AddDefaultFlag(config, "Flag_TEC");
		AddDefaultFlag(config, "Flag_UEC");
		AddDefaultFlag(config, "Flag_White");
		AddDefaultFlag(config, "Flag_Wolf");
		AddDefaultFlag(config, "Flag_Zagorky");
		AddDefaultFlag(config, "Flag_Zenit");

		return config;
	}

	protected static void AddDefaultFlag(Tokin_RandomFlagConfig config, string class_name)
	{
		config.Flags.Insert(new Tokin_RandomFlagEntry(class_name, 1.0));
	}
}
