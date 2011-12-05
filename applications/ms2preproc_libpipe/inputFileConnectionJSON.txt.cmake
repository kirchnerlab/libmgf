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
            "filterName": "MgfFileSpliterFourFilter1",
            "identifier": "MgfFileSpliterFourFilter",
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
            "filterName": "TopXFilterMerge1",
            "identifier": "TopXFilter",
            "precursors": [
                {
                    "precursorName": "MgfFileSpliterFourFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "MgfFileSpliterFourFilter1",
                    "portNameOfFilter": "MGFOutputFile1",
                    "portNameOfThis": "MGFInputFile"
                }
            ]
        },
        {
            "filterName": "TopXFilterMerge2",
            "identifier": "TopXFilter",
            "precursors": [
                {
                    "precursorName": "MgfFileSpliterFourFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "MgfFileSpliterFourFilter1",
                    "portNameOfFilter": "MGFOutputFile2",
                    "portNameOfThis": "MGFInputFile"
                }
            ]
        },
        {
            "filterName": "TopXFilterMerge3",
            "identifier": "TopXFilter",
            "precursors": [
                {
                    "precursorName": "MgfFileSpliterFourFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "MgfFileSpliterFourFilter1",
                    "portNameOfFilter": "MGFOutputFile3",
                    "portNameOfThis": "MGFInputFile"
                }
            ]
        },
        {
            "filterName": "TopXFilterMerge4",
            "identifier": "TopXFilter",
            "precursors": [
                {
                    "precursorName": "MgfFileSpliterFourFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "MgfFileSpliterFourFilter1",
                    "portNameOfFilter": "MGFOutputFile4",
                    "portNameOfThis": "MGFInputFile"
                }
            ]
        },
        {
            "filterName": "TopXInWindowsOfSizeZFilter1",
            "identifier": "TopXInWindowsOfSizeZFilter",
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
            "filterName": "MgfFilePrinterFilterTopXMerged",
            "identifier": "MgfFileMergerPrinterFilter",
            "precursors": [
                {"precursorName": "TopXFilterMerge1"},
                {"precursorName": "TopXFilterMerge2"},
                {"precursorName": "TopXFilterMerge3"},
                {"precursorName": "TopXFilterMerge4"}
            ],
            "ports": [
                {
                    "filterName": "TopXFilterMerge1",
                    "portNameOfFilter": "MGFParsedFile",
                    "portNameOfThis": "MGFOutputFile1"
                },                
                {
                    "filterName": "TopXFilterMerge2",
                    "portNameOfFilter": "MGFParsedFile",
                    "portNameOfThis": "MGFOutputFile2"
                },                
                {
                    "filterName": "TopXFilterMerge3",
                    "portNameOfFilter": "MGFParsedFile",
                    "portNameOfThis": "MGFOutputFile3"
                },                
                {
                    "filterName": "TopXFilterMerge4",
                    "portNameOfFilter": "MGFParsedFile",
                    "portNameOfThis": "MGFOutputFile4"
                }
            ]
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
        },
        {
            "filterName": "MgfFilePrinterFilterTopXInWindowsOfSizeZ",
            "identifier": "MgfFilePrinterFilter",
            "precursors": [
                {
                    "precursorName": "TopXInWindowsOfSizeZFilter1"
                }
            ],
            "ports": [
                {
                    "filterName": "TopXInWindowsOfSizeZFilter1",
                    "portNameOfFilter": "MGFParsedFile",
                    "portNameOfThis": "MGFParseFile"
                }
            ]
        }
        
    ]
}