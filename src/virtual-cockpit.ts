export class VirtualCockpit {
    ip: string
    port: number

    flightData = {}

    constructor(ip: string, port: number) {
        this.ip = ip;
        this.port = port;
    }
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
}