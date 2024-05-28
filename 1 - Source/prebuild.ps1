Write-Host "Pre-Build Script"

Write-Host "Changing version number."
$build_info_path = "XT_RefineSearchTerm\Build.ixx"

$file_config_content = Get-Content -path $build_info_path

#Write-Host $file_config_content

$build_datetime = Get-Date -Format "yyyy.MM.dd.HHmm"
$file_config_content = ($file_config_content -replace "(\s+static inline std::wstring appVersion = std::wstring\()(.*)", ('$1L"' + $build_datetime + '");'))

#Write-Host $file_config_content

$file_config_content | Set-Content $build_info_path

Write-Host "Beginning compilation."
