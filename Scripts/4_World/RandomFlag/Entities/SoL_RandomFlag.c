class SoL_RandomFlag extends Flag_White
{
	override void SetActions()
	{
		super.SetActions();

		// The folded meta-item is not intended to be attached to a flagpole.
		RemoveAction(ActionAttach);
		AddAction(SoL_ActionOpenFlag);
	}
}
