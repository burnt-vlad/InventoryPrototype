// InventoryPrototype / Fedosov Vladislav

using UnrealBuildTool;
using System.Collections.Generic;

public class InventoryPrototypeTarget : TargetRules
{
	public InventoryPrototypeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "InventoryPrototype" } );
	}
}
