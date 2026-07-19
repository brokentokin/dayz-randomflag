class Tokin_RandomFlag extends Flag_White
{
	protected float m_OpenActionSeconds;

	void Tokin_RandomFlag()
	{
		m_OpenActionSeconds = 2.0;
		RegisterNetSyncVariableFloat("m_OpenActionSeconds", 0.0, 0.0, 2);
	}

	override void EEInit()
	{
		super.EEInit();

		if (GetGame() && GetGame().IsServer())
		{
			m_OpenActionSeconds = Tokin_RandomFlagConfigManager.GetOpenActionSeconds();
			SetSynchDirty();
		}
	}

	float GetOpenActionSeconds()
	{
		if (m_OpenActionSeconds < 1.0)
			return 1.0;

		return m_OpenActionSeconds;
	}

	override void SetActions()
	{
		super.SetActions();

		// The folded meta-item is not intended to be attached to a flagpole.
		RemoveAction(ActionAttach);
		AddAction(Tokin_ActionOpenFlag);
	}
}
