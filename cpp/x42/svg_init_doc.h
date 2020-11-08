#include <string>

const std::string svg_init_doc = {R"_(<svg height="600" width="800">
                <g>
                    <defs>
                        <radialGradient id="grad1" cx="50%" cy="50%" r="50%" fx="50%" fy="50%">
                        <stop offset="0%" style="stop-color:rgb(255,255,255);
                        stop-opacity:0" />
                        <stop offset="100%" style="stop-color:rgb(0,0,255);stop-opacity:1" />
                        </radialGradient>
                    </defs>
                    <ellipse cx="{CX}" cy="{CY}" rx="85" ry="55" fill="url(#grad1)" />
                    <text x="{CX}" y="{CY}" fill="black">{TEXT}</text>
                </g>
                </svg>)_"};