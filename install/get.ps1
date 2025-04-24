# install.ps1

# Ensure script stops on error
$ErrorActionPreference = "Stop"

# Check if scoop is installed
if (-not (Get-Command scoop -ErrorAction SilentlyContinue)) {
    Write-Host "Scoop not found. Installing Scoop..."
    Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
    Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression
}

# add main bucket
scoop bucket add main

# Install dependencies
$packages = @(
    "main/cmake",
    "main/ninja",
    "main/git",
    "main/vcpkg"
)

foreach ($pkg in $packages) {
    if (-not (scoop list | Select-String $pkg)) {
        Write-Host "Installing $pkg..."
        scoop install $pkg
    } else {
        Write-Host "$pkg is already installed."
    }
}

Invoke-WebRequest `
  -Uri https://aka.ms/vs/17/release/vs_BuildTools.exe `
  -OutFile vs_BuildTools.exe

.\vs_BuildTools.exe `
  --quiet --wait --norestart --nocache `
  --add Microsoft.VisualStudio.Workload.VCTools `
  --includeRecommended `
  --lang en-US


