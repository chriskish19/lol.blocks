# check if a scoop package is installed or not
function is_spkg_installed{
    param(
        [string]$pkg_name
    )

    return Get-Command $pkg_name -ErrorAction SilentlyContinue
}



# Ensure script stops on error
$ErrorActionPreference = "Stop"

# Check if scoop is installed
if (-not (Get-Command scoop -ErrorAction SilentlyContinue)) {
    Write-Host "Scoop not found. Installing Scoop..."
    Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
    Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
}

# Desired packages (can include "main/" or other bucket prefixes)
$packages = @(
    "cmake",
    "ninja",
    "git",
    "vcpkg"
)



foreach ($pkg in $packages) {
    if (-not (is_spkg_installed($pkg))) {
        Write-Host "Installing $pkg..." -ForegroundColor Yellow
        $full_pkg_name = "main/" + $pkg
        scoop install $full_pkg_name
    } else {
        Write-Host "$pkg is already installed." -ForegroundColor Green
    }
}


# Download vs_BuildTools.exe
Invoke-WebRequest `
-Uri https://aka.ms/vs/17/release/vs_BuildTools.exe `
-OutFile vs_BuildTools.exe

# install
$startInfo = New-Object System.Diagnostics.ProcessStartInfo
$startInfo.FileName = "vs_BuildTools.exe"
$startInfo.Arguments = "--all --quiet --wait"
$process = New-Object System.Diagnostics.Process
$process.StartInfo = $startInfo
$process.Start()
$process.WaitForExit()



# install DirectX toolkit
# Check if DirectXTK is already installed via vcpkg
$dxInstalled = vcpkg list | Select-String -Pattern "^directxtk"

if (-not $dxInstalled) {
    Write-Host "Installing DirectXTK using vcpkg..." -ForegroundColor Yellow
    vcpkg install directxtk:x64-windows
}
else {
    Write-Host "DirectXTK is already installed." -ForegroundColor Green
}


