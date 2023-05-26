import { MSFS_API } from 'msfs-simconnect-api-wrapper'


export class FSConnector {
    api: MSFS_API
    
    async connect() {
        this.api = new MSFS_API()
        this.api.connect({
            async onConnect() {
                console.log("Connected to MSFS")

                const dme = await this.api.get('NAV_DME', 'NAV_ACTIVE_FREQUENCY:1')
                console.log(`DME: ${JSON.stringify(dme)}`)
            }
        })
    }
}