{
    "connections": [
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
            "filterName": "MgfFilePrinterFilter1",
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
        }
        
    ]
}