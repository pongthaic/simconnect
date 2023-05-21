import { MSFS_API } from "msfs-simconnect-api-wrapper"
import { Socket, connect } from 'net'

const deviceIp = "10.0.0.87"

async function _connectToDevice() {
    const sock = connect({ host: deviceIp, port: 8779 }, () => {
        console.log('connected.')
        update(sock);
        sock.on("data", onDataReceived)
        setInterval(() => update(sock), 1000 * 10)

        })
}

let vor1 = 117.70
let vor2 = 118.80

function update(sock) {
    sock.write(`VOR1=${(vor1).toFixed(2)}\n`)
    sock.write(`VOR2=${(vor2).toFixed(2)}\n`)
    
    vor1 += 0.10
    vor2 += 0.20

    console.log(`updated vor1 = ${(vor1).toFixed(2)} vor2 = ${(vor2).toFixed(2)}`)
}

/** @param data {Buffer} */
function onDataReceived(data) {
    const value = data.toString('ascii')
    
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