$(function () {
    var LETTERS = [
        [
            [[0, 174], [59, 0], [79, 135], [0, 162], [98, 187], [96, 108], [65, 116]],
            [[0, 2], [0, 3], [1, 3], [1, 6], [5, 6], [4, 5], [0, 4], [2, 3], [2, 4], [2, 5], [3, 6]]
        ],
        [
            [[115, 169], [204, 154], [177, 109], [126, 103], [150, 96], [188, 29], [137, 24]],
            [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 3], [6, 3], [3, 0], [0, 2]]
        ],
        [
            [[191, 66], [248, 96], [218, 155], [218, 21]],
            [[0, 1], [1, 2], [1, 3], [0, 3], [0, 2]]
        ],
        [
            [[264, 153], [281, 149], [267, 54], [263, 34], [308, 34]],
            [[0, 1], [1, 2], [2, 4], [3, 4], [0, 3]]
        ],
        [
            [[337, 149], [348, 100], [375, 90], [337, 40], [284, 81]],
            [[0, 1], [1, 2], [2, 3], [3, 4], [0, 4], [1, 4], [0, 2], [1, 3]]
        ],
        [
            [[383, 114], [402, 117], [464, 132], [436, 156], [412, 49], [461, 51], [461, 86], [432, 91], [414, 34]],
            [[0, 1], [1, 2], [2, 3], [4, 5], [5, 6], [6, 7], [5, 7], [5, 8], [0, 8], [0, 3], [1, 8]]
        ],
        [
            [[487, 148], [502, 187], [506, 142], [487, 26]],
            [[0, 3], [2, 3], [0, 2]]
        ],
        [
            [[546, 97], [544, 158], [576, 166], [597, 110], [637, 170], [687, 190], [575, 14], [576, 95], [511, 29]],
            [[0, 8], [0, 1], [1, 8], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [2, 7], [3, 5], [3, 7], [3, 6], [1, 6], [1, 7]]
        ]
    ];
    var MARKER = "M 0,0 C 0.31,0.02 0.4,-0.01 0.46,0.03 0.5,0.06 0.49,0.16 0.52,0.34 0.35,0.23 0.27,0.18 0,0 M 5.63,1.86 C 5.56,1.61 5.53,1.5 5.47,1.27 5.68,1.37 5.76,1.41 5.88,1.46 5.81,1.57 5.76,1.64 5.63,1.86 m -9.7,-11.62 c 0.41,0.14 0.6,0.21 0.87,0.3 -0.16,0.22 -0.25,0.34 -0.42,0.57 -0.15,-0.28 -0.24,-0.46 -0.45,-0.87 m 3.63,7.53 c 0.19,-0.16 0.37,-0.4 0.45,-0.37 0.19,0.08 0.34,0.27 0.55,0.46 C 0.31,-2 0.21,-1.95 0.11,-1.89 -0.03,-1.98 -0.17,-2.06 -0.44,-2.23 M 8.62,-6.97 C 8.1,-7.09 7.85,-7.08 7.76,-7.19 7.65,-7.35 7.65,-7.6 7.67,-7.8 c 0,-0.05 0.34,-0.16 0.38,-0.12 0.16,0.19 0.27,0.43 0.57,0.95 m -0.59,-5.15 c -0.31,-0.21 -0.63,-0.41 -1.11,-0.73 0.73,1.14 1.34,2.09 1.97,3.08 l -0.35,0 c 0.2,0.31 0.38,0.6 0.56,0.89 -0.04,0.03 -0.08,0.07 -0.12,0.1 -1.01,-1.23 -2.02,-2.45 -3.3,-4 0.5,1.16 0.82,1.92 1.14,2.68 -0.04,0.02 -0.08,0.04 -0.12,0.07 -0.8,-1.18 -1.6,-2.37 -2.5,-3.71 1.05,3.28 2.03,6.38 3.02,9.47 C 7.16,-4.25 7.11,-4.22 7.05,-4.2 6.44,-5.32 5.82,-6.44 5.04,-7.88 l 0,8.38 C 4.22,-1.55 3.47,-3.48 2.59,-5.71 2.22,-3.95 1.93,-2.53 1.64,-1.12 1.54,-1.13 1.44,-1.13 1.34,-1.14 l 0,-7.73 c -0.1,0 -0.19,-0.01 -0.29,-0.02 -0.84,2.49 -1.68,4.97 -2.52,7.46 -0.03,-0.01 -0.06,-0.01 -0.09,-0.02 0.21,-1.32 0.42,-2.63 0.67,-4.25 -0.94,1.4 -1.69,2.53 -2.59,3.88 0.71,-2.43 1.34,-4.6 1.98,-6.79 -0.49,0.42 -0.97,0.83 -1.72,1.47 1.12,-2.64 2.09,-4.94 3.16,-7.47 -2.05,1.94 -3.91,3.71 -5.94,5.63 0.61,-0.87 1.09,-1.55 1.65,-2.34 -0.5,0.28 -0.85,0.47 -1.2,0.67 1.72,-2.01 3.56,-3.83 5.51,-5.52 1.07,-0.93 2.43,-1.28 3.73,-0.53 0.78,0.45 1.37,1.23 2.01,1.89 1.06,1.09 2.1,2.2 3.04,3.19 -0.12,-0.09 -0.38,-0.27 -0.64,-0.45 -0.01,-0.01 -0.02,-0.02 -0.04,-0.04";

    var WIDTH = 800, HEIGHT = 190;
    var nodes = [], links = [], colors = [];
    var arrow_data = {x: 0, y: 0, a: 0};

    LETTERS.forEach(function () {
        colors.push(Math.random() > 0.5);
    });

    function randint(m) {
        return parseInt(Math.random() * m);
    }

    function color_for(e) {
        return e ? '#00adef' : '#80cc28';
    }

    function arrow_apply(tr) {
        tr.attr('transform', 'translate(' + [arrow_data.x, arrow_data.y] + ')');
        tr.select('.subarrow').attr('transform', 'rotate(' + arrow_data.a + ')');
    }

    function arrow_move_to(pos) {
        arrow_data.x = pos.x;
        arrow_data.y = pos.y;
        arrow_apply(arrow);
    }

    function arrow_go_to(pos) {
        pos = {x: pos.x, y: pos.y};
        var tr = d3.transform(arrow.attr('transform'));
        arrow_data.a = Math.atan2(pos.y - tr.translate[1], pos.x - tr.translate[0]) * 180 / Math.PI;
        arrow.transition()
            .duration(1000)
            .call(arrow_apply)
        arrow_data.x = pos.x;
        arrow_data.y = pos.y;
        arrow.transition().delay(1000).duration(2000).call(arrow_apply);
    }

    var i = 0;
    LETTERS.forEach(function (letterdef, j) {
        var lnodes = letterdef[0], llinks = letterdef[1];
        var color = colors[j];
        lnodes.forEach(function (d) {
            var x = d[0], y = HEIGHT - d[1];
            nodes.push({gid: j, x: x, y: y, color: color});
        });
        llinks.forEach(function (d) {
            links.push({gid: j, source: d[0] + i, target: d[1] + i, color: color});
        });
        i += lnodes.length;
    });

    var force = d3.layout.force()
            .nodes(nodes)
            .links(links)
            .size([WIDTH, HEIGHT])
            .gravity(0)
            .charge(0)
            .linkStrength(0)
            .on('tick', tick)
            .start()
        ;

    var svg = d3.select('.navbar .container').insert('svg', ':first-child')
        .attr('id', 'header-anim')
        .attr('width', WIDTH)
        .attr('height', HEIGHT);

    var root = svg.append('g').attr('transform', 'translate(30 20) scale(0.6)');

    var defs = svg.append('defs');
    defs.append('g').attr('id', 'marker').append('path').attr('d', MARKER).attr('transform', 'translate(-1 -16) scale(1 -1) ');
    defs.append('g').attr('id', 'markerpos').append('ellipse').attr('rx', 11).attr('ry', 7);

    var edges = root.selectAll('.edge')
        .data(links)
        .enter()
        .append('line').attr('class', 'edge');
    var points = root.selectAll('.point')
        .data(nodes)
        .enter().append('g').attr('class', 'point');

    points.append('use').attr('xlink:href', '#markerpos')
        .attr('class', 'markerpos').attr('stroke', 'none');

    points.append('use').attr('xlink:href', '#marker')
        .attr('class', 'marker').attr('fill', 'none');

    var arrow = root.append('g').attr('class', 'arrow');
    arrow.append('circle').attr('class', 'circle').attr('r', 22).attr('fill', 'none').attr('stroke', '#f5792e').attr('stroke-width', 1);
    var subarrow = arrow.append('g').attr('class', 'subarrow').append('g').attr('transform', 'scale(0.4) translate(-70 -70)');
    subarrow.append('path').attr('fill', '#f5792e').attr('d', 'm41.742756,55.314041l3.462505,18.875008l-3.462505,18.887482l60.624996,-18.887482l-60.624996,-18.875008zm1.200008,1.362495l56.262489,17.524986l-56.262489,17.525024l3.174992,-17.362518l0.037498,-0.162506l-0.025005,-0.17498l-3.174992,-17.350006l-0.012493,0z');
    subarrow.append('path').attr('fill', '#f5792e').attr('d', 'm44.457176,50.807293l3.462505,18.875004l-3.462505,18.875008l60.625,-18.875008l-60.625,-18.875004z');
    subarrow.append('path').attr('fill', '#ffffff').attr('d', 'm48.520306,53.683163l2.712498,14.824978l-2.712498,14.82502l47.612492,-14.82502l-47.612492,-14.824978z');

    force.tick();
    force.stop();
    apply_color();

    function apply_color(duration, delay) {
        if (duration === undefined)
            duration = 0;
        if (delay === undefined)
            delay = 0;
        points.select('.markerpos')
            .transition().delay(delay).duration(duration).attr('stroke', function (d) {
                return color_for(d.color);
            });
        points.select('.marker')
            .transition().delay(delay).duration(duration).attr('fill', function (d) {
                return color_for(d.color);
            });
        edges
            .transition().delay(delay).duration(duration).attr('stroke', function (d) {
                return color_for(d.color);
            });
    }

    function tick() {
        points
            .attr('transform', function (d) {
                return 'translate(' + [d.x, d.y] + ')';
            });
        edges
            .attr('x1', function (d) {
                return d.source.x;
            })
            .attr('y1', function (d) {
                return d.source.y;
            })
            .attr('x2', function (d) {
                return d.target.x;
            })
            .attr('y2', function (d) {
                return d.target.y;
            });
    }

    var cur_node = randint(nodes.length), visited = [cur_node];
    arrow_move_to(nodes[cur_node]);

    function random_arrow_move() {
        var n = nodes[cur_node];
        var el = links.filter(function (d) {
            return d.gid == n.gid && (d.target.index == n.index || d.source.index == n.index);
        });
        var targets = [];
        el.forEach(function (l) {
            if (l.source.index != n.index && visited.indexOf(l.source.index) == -1)
                targets.push(l.source.index);
            if (l.target.index != n.index && visited.indexOf(l.target.index) == -1)
                targets.push(l.target.index);
        });
        if (!targets.length) {
            // no more targets on this letter, go somewhere else
            while (true) {
                var l = links[randint(links.length)];
                if (l.gid != cur_node.gid)
                    break;
            }
            cur_node = l.source.index;
            visited = [];
        } else {
            cur_node = targets[randint(targets.length)];
        }
        var last_node = visited.slice(-1)[0];
        visited.push(cur_node);
        //if (last_node !== undefined) {
        //    var link = links.filter(function (d) {
        //        return d.target.index == last_node && d.source.index == cur_node ||
        //            d.source.index == last_node && d.target.index == cur_node;
        //    })[0];
        //    var orig = link.source.index == cur_node ? link.target : link.source;
        //    orig.color = !orig.color;
        //    link.color = orig.color;
        //    apply_color(2000, 1000);
        //}
        arrow_go_to(nodes[cur_node]);
    }

    random_arrow_move();
    setInterval(random_arrow_move, 3000);

});
