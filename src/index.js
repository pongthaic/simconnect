import { MSFS_API } from "msfs-simconnect-api-wrapper"
import { connect } from 'net'

const deviceIp = "10.0.0.87"

async function _connectToDevice() {
    const sock = connect({ host: deviceIp, port: 8779 }, () => {
            console.log('connected.')
        sock.write("VOR1=117.70\n")
        sock.write("VOR2=118.80\n")
        })
}

async function main() {
    await _connectToDevice();
    /*
    const api = new MSFS_API()
    api.connect({
        async onConnect() {
            console.log("Connected to MSFS")

            const dme = await api.get('NAV_DME', 'NAV_ACTIVE_FREQUENCY:1')
            console.log(`DME: ${JSON.stringify(dme)}`)
        }
    })
    */
}

main()