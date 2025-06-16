Write-Host "============================"
Write-Host "    Start of:"
Write-Host "Post Build Script"
Write-Host "============================"

# Parse arguments
$app_name = $Args[0]
$build_path = $Args[1]
$app_build_configuration = $Args[2]
$XTensionFolder = "C:\Program Files\X-Ways Forensics\XTensions\" + $app_name + "\"

Write-Host "App name: $app_name"
Write-Host "Build Path: $build_path"
Write-Host "Configuration: $app_build_configuration"
Write-Host "Xtension Folder: $XTensionFolder"
Write-Host "Post-Build Script - $app_build_configuration Mode"

# xcopy /y /d /f "$(OutDir)$(TargetFileName)" "C:\Program Files\X-Ways Forensics\XTensions"

Write-Host "Creating XTension Folder."

# Create the release folder.
New-Item -Path "$XTensionFolder" -ItemType "directory" -erroraction 'SilentlyContinue' | Out-Null

Write-Host "Copying items to XTension folder."

Copy-Item $build_path -Destination $XTensionFolder -Force -Recurse | Out-Null

Write-Host "Post build script completed."


Write-Host "============================"
Write-Host "     End of:"
Write-Host "Post Build Script"
Write-Host "============================"