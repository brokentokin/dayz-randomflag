class SoL_ActionOpenFlagCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(10.0);
	}
}

class SoL_ActionOpenFlag : ActionContinuousBase
{
	void SoL_ActionOpenFlag()
	{
		m_CallbackClass = SoL_ActionOpenFlagCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "Open Flag";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		SoL_RandomFlag folded_flag = SoL_RandomFlag.Cast(item);
		return folded_flag && player.GetItemInHands() == folded_flag;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		PlayerBase player = action_data.m_Player;
		SoL_RandomFlag folded_flag = SoL_RandomFlag.Cast(action_data.m_MainItem);

		if (!player || !folded_flag || player.GetItemInHands() != folded_flag)
			return;

		string selected_classname = SoL_RandomFlagConfigManager.GetRandomFlagClassName();
		if (selected_classname == "")
		{
			ErrorEx("[Random Flag] Open Flag could not select a valid classname. The Folded Flag was preserved.");
			return;
		}

		SoL_RandomFlagReplaceLambda replace_lambda = new SoL_RandomFlagReplaceLambda(folded_flag, selected_classname, player);
		if (!player.ServerReplaceItemInHandsWithNew(replace_lambda))
		{
			// A rejected hand event never executes the lambda, so invoke the same
			// inventory/ground fallback used by OnAbort.
			replace_lambda.TryFallbackPlacement();
		}
	}
}

class SoL_RandomFlagReplaceLambda : ReplaceItemWithNewLambda
{
	protected bool m_FallbackAttempted;

	void SoL_RandomFlagReplaceLambda(EntityAI old_item, string new_item_type, PlayerBase player)
	{
		m_FallbackAttempted = false;
	}

	override void OnSuccess(EntityAI new_item)
	{
		super.OnSuccess(new_item);

		if (new_item)
		{
			Print("[Random Flag] Opened Folded Flag into " + new_item.GetType() + " in the player's hands.");
			PlayOptionalOpenSound();
		}
	}

	override void OnAbort()
	{
		super.OnAbort();
		TryFallbackPlacement();
	}

	void TryFallbackPlacement()
	{
		if (m_FallbackAttempted)
			return;

		m_FallbackAttempted = true;

		if (!m_Player || !m_OldItem || m_Player.GetItemInHands() != m_OldItem)
		{
			ErrorEx("[Random Flag] Replacement was aborted after the Folded Flag left the player's hands. No reward was created.");
			return;
		}

		EntityAI new_item = m_Player.GetInventory().CreateInInventory(m_NewItemType);
		if (new_item)
		{
			m_OldItem.DeleteSafe();
			Print("[Random Flag] Opened Folded Flag into " + new_item.GetType() + " in the player's inventory.");
			PlayOptionalOpenSound();
			return;
		}

		new_item = EntityAI.Cast(GetGame().CreateObjectEx(m_NewItemType, m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
		if (new_item)
		{
			m_OldItem.DeleteSafe();
			Print("[Random Flag] Opened Folded Flag into " + new_item.GetType() + " on the ground.");
			PlayOptionalOpenSound();
			return;
		}

		ErrorEx("[Random Flag] Could not create " + m_NewItemType + " in hands, inventory, or on the ground. The Folded Flag was preserved.");
	}

	protected void PlayOptionalOpenSound()
	{
		/*
			Optional custom sound hook, intentionally disabled.

			A multiplayer-ready implementation should send a small RPC to nearby
			clients, then play a configured SoundSet on those clients with:

			SEffectManager.PlaySound("Your_Open_Flag_SoundSet", m_Player.GetPosition());

			The core mod does not register an RPC or require a sound asset.
		*/
	}
}
