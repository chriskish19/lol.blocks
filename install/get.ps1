# dl the installer
Invoke-WebRequest -Uri "https://aka.ms/vs/17/release/vs_community.exe" -OutFile "vs_community.exe"

# install vs2022 full ide, git, cmake and ninja
Start-Process ".\vs_community.exe" -ArgumentList "--wait" , "--norestart","--add","Microsoft.VisualStudio.Workload.NativeDesktop","Microsoft.VisualStudio.Component.VC.CMake.Project","Microsoft.VisualStudio.Component.Ninja","Microsoft.VisualStudio.Component.Git","--includeRecommended" -Wait



# check if a scoop package is installed or not
function is_spkg_installed{
    param(
        [string]$pkg_name
    )

    return Get-Command $pkg_name -ErrorAction SilentlyContinue
}


# Check if scoop is installed
if (-not (Get-Command scoop -ErrorAction SilentlyContinue)) {
    Write-Host "Scoop not found. Installing Scoop..."
    Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
    Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
}

# Desired packages (can include "main/" or other bucket prefixes)
$packages = @(
    "vcpkg"
)

# install scoop packages
foreach ($pkg in $packages) {
    if (-not (is_spkg_installed($pkg))) {
        Write-Host "Installing $pkg..." -ForegroundColor Yellow
        $full_pkg_name = "main/" + $pkg
        scoop install $full_pkg_name
    } else {
        Write-Host "$pkg is already installed." -ForegroundColor Green
    }
}

# integrate vcpkg to install for vs2022
if (-not (Get-Command vcpkg integrate install -ErrorAction SilentlyContinue)){
    Write-Host "Error vcpkg not installed..." -ForegroundColor Red
}

# install directxtk
if (-not (Get-Command vcpkg install directxtk -ErrorAction SilentlyContinue)){
    Write-Host "Error vcpkg not installed..." -ForegroundColor Red
}
