# distance-jump

download [Max](https://cycling74.com/downloads)

run `jump.maxpat` to process sensor signals

## initial setup

- connect sensors to inputs 1-9 in the switch
- connect PC to input 10 in the switch
- power on the switch, sensors & PC

in Windows 10, hit Start > "Ethernet Settings", click on "Unidentified network"

under IP settings, click "Edit" and choose "Manual" instead of Automatic (DHCP)

turn on IPv4 and set:
- IP: `169.254.25.10`
- Subnet prefix length: `24`
- Gateway: `169.254.25.11`

click "Save"

## diagnostics

run `cmd` to open a Command Prompt, then
- run `ipconfig` to check your IP (under `Ethenet adapter Ethernet`)
- run `arp -a` to check that all sensor IPs are present in the network
    - you should see `169.254.25.1` - `169.254.25.9`
