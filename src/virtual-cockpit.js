import fetch from 'node-fetch'

export class VirtualCockpit {
    ip;
    port = 80;

    flightData = {}

    constructor(ip, port) {
        this.ip = ip;
        this.port = port;
    }

    async init(port) {
        await fetch(`http://${ip}:${port}/init?${this.formatFlightData(flightData)}`)
    }

    formatFlightData() {
        return Object.entries(flightData).map((k,v) => `${encodeURIComponent(k)}=${encodeURIComponent(v)}`).join('&')
    }
}