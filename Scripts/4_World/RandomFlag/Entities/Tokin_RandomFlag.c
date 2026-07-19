class Tokin_RandomFlag extends Flag_White
{
	override void SetActions()
	{
		super.SetActions();

		// The folded meta-item is not intended to be attached to a flagpole.
		RemoveAction(ActionAttach);
		AddAction(Tokin_ActionOpenFlag);
	}
}
