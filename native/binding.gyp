{
    "targets": [
        {
            "include_dirs" : [
                "<!(node -e \"require('nan')\")"
            ],
            "link_settings" : {
                "ldflags": [
                        "-Wl,-z,defs"
                    ]
            },
            "sources": [
                "main.cpp",
                "<!@(ls -1 **/*.cpp)",
                "<!@(ls -1 **/*.hpp"
            ],
            "target_name": "addon"
        }
    ]
}