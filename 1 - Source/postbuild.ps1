Write-Host "============================"
Write-Host "    Start of:"
Write-Host "Post Build Script"
Write-Host "============================"

# Parse arguments
$app_name = $Args[0]
$build_path = $Args[1]
$app_build_configuration = $Args[2]
$project_path = $Args[3]
$XTensionFolder = "C:\Program Files\X-Ways Forensics\XTensions\" + $app_name + "\"
$resource_path = $project_path + "Resources\"

Write-Host "App name: $app_name"
Write-Host "Project Path: $project_path"
Write-Host "Resources Path: $resource_path"
Write-Host "Build Path: $build_path"
Write-Host "Configuration: $app_build_configuration"
Write-Host "Xtension Folder: $XTensionFolder"
Write-Host "Post-Build Script - $app_build_configuration Mode"

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