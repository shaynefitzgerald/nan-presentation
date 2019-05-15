{
    "targets": [
        {
        "include_dirs" : [
            "<!(node -e \"require('nan')\")"
        ],
        "sources": [
            "main.cpp", "polygon.hpp", "polygon.cpp"
        ],
        "target_name": "slicker-compute",
        }
    ]
}