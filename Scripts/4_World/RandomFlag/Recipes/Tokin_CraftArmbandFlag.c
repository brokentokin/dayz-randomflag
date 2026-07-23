modded class CraftArmbandFlag
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		if (Tokin_RandomFlag.Cast(ingredients[0]))
			return false;

		return super.CanDo(ingredients, player);
	}
}
