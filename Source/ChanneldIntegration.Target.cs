using UnrealBuildTool;
using System.Collections.Generic;

public class ChanneldIntegrationTarget : TargetRules
{
	public ChanneldIntegrationTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "ChanneldIntegration" } );
	}
}
