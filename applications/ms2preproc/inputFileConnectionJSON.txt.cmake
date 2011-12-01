{
    "connections": [
        {
            "filterName": "TopXInYRegionsFilter1",
            "identifier": "TopXInYRegionsFilter",
            "precursors": [
                {
                    "precursorName": "MgfFileReaderFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "MgfFileReaderFilter1",
                    "portNameOfFilter": "MGFInputFile",
                    "portNameOfThis": "MGFInputFile"
                }
            ]
        },
        {
            "filterName": "TopXFilter1",
            "identifier": "TopXFilter",
            "precursors": [
                {
                    "precursorName": "MgfFileReaderFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "MgfFileReaderFilter1",
                    "portNameOfFilter": "MGFInputFile",
                    "portNameOfThis": "MGFInputFile"
                }
            ]
        },
        {
            "filterName": "MgfFileReaderFilter1",
            "identifier": "MgfFileReaderFilter",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "MgfFilePrinterFilterTopX",
            "identifier": "MgfFilePrinterFilter",
            "precursors": [
                {
                    "precursorName": "TopXFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "TopXFilter1",
                    "portNameOfFilter": "MGFParsedFile",
                    "portNameOfThis": "MGFParseFile"
                }
            ]
        },
        {
            "filterName": "MgfFilePrinterFilterTopXInYRegions",
            "identifier": "MgfFilePrinterFilter",
            "precursors": [
                {
                    "precursorName": "TopXInYRegionsFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "TopXInYRegionsFilter1",
                    "portNameOfFilter": "MGFParsedFile",
                    "portNameOfThis": "MGFParseFile"
                }
            ]
        }
        
    ]
}