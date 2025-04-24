# install.ps1

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
    "main/cmake",
    "main/ninja",
    "main/git",
    "main/vcpkg"
)

# Get only installed package names (skip the header, get 1st column)
$installed = (scoop list) -replace ' +', ' ' | Select-Object -Skip 1 | ForEach-Object {
    ($_ -split ' ')[0].Trim()
}

foreach ($pkg in $packages) {
    # Extract only the package name (ignore bucket prefix like "main/")
    $pkgName = ($pkg -split '/')[1]
    
    if ($installed -notcontains $pkgName) {
        Write-Host "Installing $pkg..." -ForegroundColor Yellow
        scoop install $pkg
    } else {
        Write-Host "$pkgName is already installed." -ForegroundColor Green
    }
}



# Check for existing VS Build Tools installation
$vsPath = Get-ItemProperty -Path "HKLM:\SOFTWARE\WOW6432Node\Microsoft\VisualStudio\SxS\VS7" -ErrorAction SilentlyContinue

if ($vsPath -and ($vsPath."17.0" -or $vsPath."16.0")) {
    Write-Host "Visual Studio Build Tools are already installed." -ForegroundColor Green
}
else {
    Write-Host "Downloading and installing Visual Studio Build Tools..." -ForegroundColor Yellow

    # Download vs_BuildTools.exe
    Invoke-WebRequest `
        -Uri https://aka.ms/vs/17/release/vs_BuildTools.exe `
        -OutFile vs_BuildTools.exe

    # Run installer
    Start-Process .\vs_BuildTools.exe -Wait -ArgumentList @(
        "--quiet",
        "--wait",
        "--norestart",
        "--nocache",
        "--add", "Microsoft.VisualStudio.Workload.VCTools",
        "--includeRecommended",
        "--lang", "en-US"
    )

    Write-Host "Installation complete."
}



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


