import { FlightData, VirtualCockpit } from './virtual-cockpit'
export class DeviceConnector {
    constructor(readonly ip: string, readonly port: number, readonly vc: VirtualCockpit) {
    }

    async initialize() {
        this.send(FlightData.toString())
    }

    async send(message: string) {

    }

    async receive(message: string) {

    }
}