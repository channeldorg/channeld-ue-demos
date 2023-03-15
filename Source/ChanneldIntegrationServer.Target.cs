using UnrealBuildTool;
using System.Collections.Generic;

public class ChanneldIntegrationServerTarget : TargetRules
{
	public ChanneldIntegrationServerTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "ChanneldIntegration" } );
	}
}
