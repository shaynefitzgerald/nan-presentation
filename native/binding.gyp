{
    "targets": [
        {
        "include_dirs" : [
            "<!(node -e \"require('nan')\")",
            "polygon", "point", "line"
        ],
        "sources": [
            "main.cpp",
            "<!@(ls -1 **/*.cpp)"
        ],
        "target_name": "slicker-compute",
        }
    ]
}