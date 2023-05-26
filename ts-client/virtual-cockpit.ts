export class VirtualCockpit {
    ip: string
    port: number

    flightData: FlightData = new FlightData()
}

export class FlightData {
    input: {
        VOR1: number
        VOR2: number
        AP_ALT: number  // Altitiude
        AP_CRS: number  // Course
        AP_HDG: number  // Heading
        AP_VSPD: number // Virtical Speed
        AP_SPD: number // Air Speed
    }

    display: {
        ALT: number // Current Altitude (ft.)
        SPD: number // Current Airspeed
        DME1: number // Distance VOR1 or FMC
        DME2: number // Distance VOR2
    }

    nonDisplay: {
        GEAR: boolean // True = DOWN
        LIGHT: boolean // Landing Light
        TAXI: boolean // Taxi Light
        DOME: boolean // Dome Light
        ELVTRIM: number // Elevator Trim
    }

    constructor() {
        this.input = {
            VOR1: 110.80,
            VOR2: 110.80,
            AP_ALT: 0,
            AP_CRS: 1,
            AP_HDG: 1,
            AP_VSPD: 0,
            AP_SPD: 0,
        }
        this.display = {
            ALT: 0,
            SPD: 0,
            DME1: 0,
            DME2: 0,
        }
        this.nonDisplay = {
            GEAR: false,
            LIGHT: false,
            TAXI: false,
            DOME: false,
            ELVTRIM: 0,
        }
    }

    toString(): string {
        return "" +
            Object.entries(this.input).map(([k, v]) => `I ${k} ${v}`).join('\n') +
            Object.entries(this.display).map(([k, v]) => `D ${k} ${v}`).join('\n') +
            Object.entries(this.nonDisplay).map(([k,v]) => `N ${k} ${v}`).join('\n')
    }
}
