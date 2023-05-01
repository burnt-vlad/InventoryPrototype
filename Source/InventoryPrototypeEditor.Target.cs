// InventoryPrototype / Fedosov Vladislav

using UnrealBuildTool;
using System.Collections.Generic;

public class InventoryPrototypeEditorTarget : TargetRules
{
	public InventoryPrototypeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "InventoryPrototype" } );
	}
}
