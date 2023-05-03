import { MSFS_API } from "msfs-simconnect-api-wrapper"

const deviceIp = "10.0.0.88"

async function main() {
    const api = new MSFS_API()
    api.connect({
        async onConnect() {
            console.log("Connected to MSFS")

        const dme = await api.get('NAV_DME', 'NAV_ACTIVE_FREQUENCY:1')
        console.log(`DME: ${JSON.stringify(dme)}`)
        }
    })
}

main()