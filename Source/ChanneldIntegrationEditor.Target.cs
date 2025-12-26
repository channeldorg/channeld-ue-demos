using UnrealBuildTool;
using System.Collections.Generic;

public class ChanneldIntegrationEditorTarget : TargetRules
{
	public ChanneldIntegrationEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "ChanneldIntegration" } );
	}
}
