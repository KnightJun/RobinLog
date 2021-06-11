-- add rules: debug/release
add_rules("mode.debug", "mode.release")
add_requires("spdlog"  , {debug = is_mode("debug")})

-- define target
target("RobinLog")
    -- set kind
    add_rules("qt.shared")
    add_packages("spdlog")
    add_frameworks("QtCore")
    -- add files
    add_files("RobinLog.cpp")
    add_headerfiles("RobinLog.h")
    add_defines("ROBINLOG_LIB")
