$(function () {

    var MAP_CELLS = 30,
        CELL_SIZE = 19,
        EVENT_DURATION = 600,
        COLORS = ['#00adef', '#80cc28'],
        GRID_COLOR = '#333';

    var turn_count, player_map = {}, players = [], portals = [], edges = [], triangles = [];
    var svg_players, svg_portals, svg_edges, svg_triangles;

    function svg_translate(d) {
        return 'translate(' + [(d.x + .5) * CELL_SIZE, (d.y + .5) * CELL_SIZE] + ')';
    }

    function svg_build_player(selection) {
        var color = function (d) {
            return d.color;
        };
        var g = selection.append('g').attr('class', 'player').append('g').attr('transform', 'translate(-25 -25) scale(' + (CELL_SIZE / 63 * 1.2) + ')');
        // g.append('path').attr('stroke', 'white').attr('fill', 'black').attr('d', 'm41.742756,55.314041l3.462505,18.875008l-3.462505,18.887482l60.624996,-18.887482l-60.624996,-18.875008zm1.200008,1.362495l56.262489,17.524986l-56.262489,17.525024l3.174992,-17.362518l0.037498,-0.162506l-0.025005,-0.17498l-3.174992,-17.350006l-0.012493,0z');
        g.append('path').attr('fill', color).attr('d', 'm48.520306,53.683163l2.712498,14.824978l-2.712498,14.82502l47.612492,-14.82502l-47.612492,-14.824978z');
    }

    function gen_grid(el, horizontal) {
        var id = function (d) {
            return d;
        };
        var end = MAP_CELLS * CELL_SIZE;
        var x1, x2, y1, y2;
        if (horizontal) {
            x1 = id;
            y1 = 0;
            x2 = id;
            y2 = end;
        } else {
            x1 = 0;
            y1 = id;
            x2 = end;
            y2 = id;
        }
        el.append('g')
            .selectAll("line")
            .data(d3.range(CELL_SIZE, end, CELL_SIZE))
            .enter()
            .append("line").attr("x1", x1).attr("y1", y1).attr("x2", x2).attr("y2", y2)
            .attr('stroke', GRID_COLOR).attr('stroke-width', '1').attr('shape-rendering', 'crispEdges');
    }

    function render_turn(data) {
        // update player data
        var i = 0;
        for (var p in data.players) {
            p = parseInt(p);
            players[player_map[p]] = $.extend({}, players[player_map[p]], data.players[p]);
            $('.replay-player[data-id="' + p + '"] .score')
                .text(players[player_map[p]].score);
        }
        portals = data.map.portals;
        edges = data.map.edges;
        triangles = data.map.triangles;

        var coord = function (member, attr) {
            return function (d) {
                return (portals[d[member]][attr] + .5) * CELL_SIZE;
            };
        };

        svg_edges = svg_content
            .selectAll('.edge')
            .data(edges, function (d) {
                return String([d.from, d.to]);
            });
        // edges.build
        svg_edges.enter()
            .append('g').attr('class', 'edge')
            .append('line');
        // edges.remove
        svg_edges.exit().transition().delay(EVENT_DURATION / 2).duration(0).remove();
        // edges.update
        svg_edges.select('line')
            .transition().delay(EVENT_DURATION / 2).duration(0)
            .attr('x1', coord('from', 'x'))
            .attr('y1', coord('from', 'y'))
            .attr('x2', coord('to', 'x'))
            .attr('y2', coord('to', 'y'))
            .attr('stroke', function (d) {
                return COLORS[player_map[portals[d.from].owner]];
            });

        svg_triangles = svg_content
            .selectAll('.triangle')
            .data(triangles, function (d) {
                return String([d.s0, d.s1, d.s2]);
            });
        // triangles.build
        svg_triangles.enter()
            .append('g').attr('class', 'triangle')
            .append('path')
            .attr('opacity', '0.2')
            .attr('stroke', 'none');
        // triangles.remove
        svg_triangles.exit().transition().delay(EVENT_DURATION / 2).duration(0).remove();
        // triangles.update
        svg_triangles.select('path')
            .transition().delay(EVENT_DURATION / 2).duration(0)
            .attr('d', function (d) {
                return 'M ' + coord('s0', 'x')(d) + ',' + coord('s0', 'y')(d) +
                    'L ' + coord('s1', 'x')(d) + ',' + coord('s1', 'y')(d) +
                    'L ' + coord('s2', 'x')(d) + ',' + coord('s2', 'y')(d) +
                    'Z';
            })
            .attr('fill', function (d) {
                return COLORS[player_map[portals[d.s0].owner]];
            });

        svg_portals = svg_content
            .selectAll('.portal')
            .data(portals, function (d) {
                return String([d.x, d.y]);
            });
        // portals.build
        var el_portal = svg_portals.enter().append('g').attr('class', 'portal');
        el_portal.append('rect').attr('class', 'portal-marker')
            .attr('width', CELL_SIZE * .45).attr('height', CELL_SIZE * .45)
            .attr('transform', 'translate(-4 -4)')
            .attr('shape-rendering', 'crispEdges')
            .attr('fill', 'none')
            .attr('r', CELL_SIZE * 0.25);
        el_portal.append('text').attr('class', 'portal-shield')
            .attr('stroke', 'none')
            .attr('transform', 'translate(8 -5)');
        // portals.remove
        svg_portals.exit().transition().delay(EVENT_DURATION / 2).duration(0).remove();
        // portals.update
        svg_portals.attr('transform', svg_translate);
        svg_portals
            .transition().delay(EVENT_DURATION / 2).duration(EVENT_DURATION / 2)
            .select('.portal-marker')
            .attr('stroke', function (d) {
                if (d.owner === null)
                    return '#777';
                var new_color = COLORS[player_map[d.owner]];
                var old_color = d3.select(this).attr('stroke');
                if (old_color && new_color && old_color !== new_color) {
                    // fancy round splash on portal capture
                    setTimeout(function () {
                        svg_content.append('circle')
                            .attr('r', CELL_SIZE / 3)
                            .attr('fill', 'none')
                            .attr('stroke', new_color)
                            .attr('stroke-width', 1.5)
                            .attr('transform', svg_translate(d))
                            .attr('opacity', 1)
                            .transition().ease('linear').duration(EVENT_DURATION * 2)
                            .attr('r', CELL_SIZE * 1.5)
                            .attr('opacity', 0)
                            .transition().duration(0).remove();
                    }, EVENT_DURATION / 2);
                }
                return new_color;
            });
        svg_portals
            .select('.portal-shield')
            .transition().delay(EVENT_DURATION / 2).duration(EVENT_DURATION / 2)
            .attr('fill', function (d) {
                return COLORS[player_map[d.owner]];
            })
            .text(function (d) {
                if (d.owner === null)
                    return '';
                var that = d3.select(this),
                    old_value = that.text();
                if (d.shields && old_value != d.shields.toString()) {
                    // fancy shield splash
                    setTimeout(function () {
                        var cont = d3.select(that.node().parentNode);
                        cont.append('text')
                            .attr('transform', 'translate(8 -5)')
                            .attr('stroke', 'none')
                            .attr('fill', COLORS[player_map[d.owner]])
                            .text(d.shields)
                            .attr('opacity', 1)
                            .transition().ease('cubic-in').duration(EVENT_DURATION * 2)
                            .attr('transform', 'translate(8 -30)')
                            .attr('opacity', 0)
                            .transition().duration(0).remove();
                    }, EVENT_DURATION / 2);
                }
                return d.shields <= 0 ? '' : d.shields;
            });

        svg_players = svg_content
            .selectAll('.player')
            .data(players, function (d) {
                return d.id;
            });
        // players.build
        svg_players.enter().call(svg_build_player);
        // no need for players.remove
        // players.update
        svg_players.transition().ease('cubic-out').duration(EVENT_DURATION / 2).attr('transform', function (d) {
            var x = (d.x + .5) * CELL_SIZE, y = (d.y + .5) * CELL_SIZE;
            var tr = d3.transform(d3.select(this).attr('transform'));
            var a = tr.rotate;
            if (!(tr.translate[0] == x && tr.translate[1] == y))
                a = Math.atan2(y - tr.translate[1], x - tr.translate[0]) * 180 / Math.PI;
            return 'translate(' + [x, y] + ') rotate(' + a + ')';
        });
    }

    var el_replay = $('#replay'),
        el_playpause = $('#replay-playpause'),
        el_previous = $('#replay-previous'),
        el_next = $('#replay-next'),
        el_turn_label = $('#replay-turn-label'),
        el_turn_slider = $('#replay-turn-slider');

    var playing = false, event_ind, playing_timer;

    el_replay.hide();

    // build the game board
    var svg = d3.select('#replay-board').append('svg')
        .attr('width', MAP_CELLS * CELL_SIZE)
        .attr('height', MAP_CELLS * CELL_SIZE)
        .attr('style', 'box-sizing: content-box; border: 2px solid ' + GRID_COLOR);
    svg.append('rect').attr('width', MAP_CELLS * CELL_SIZE).attr('height', MAP_CELLS * CELL_SIZE).attr('fill', 'black');
    var svg_grid = svg.append('g').attr('id', 'grid');
    var svg_content = svg.append('g').attr('id', 'content');

    // render grid
    gen_grid(svg_grid, true);
    gen_grid(svg_grid, false);

    // get the dump and let the party begin
    $.get("dump/", function (game_data) {
        var events = game_data.split("\n").filter(Boolean).map(JSON.parse);

        // use first state as init
        var data = events[0];
        turn_count = data.turn[1];

        var legend = $('#replay-legend').empty();
        var i = 0;
        for (var p in data.players) {
            var player = data.players[p];
            p = parseInt(p);
            player_map[p] = i;
            player.id = p;
            player.color = COLORS[i];
            players.push(player);
            // build the key (legend)
            var el = $('<div/>').attr('data-id', p).addClass('replay-player');
            var svg = d3.select(el[0]).append('svg').attr('width', CELL_SIZE * 1.2).attr('height', CELL_SIZE);
            svg.selectAll('.player').data([player]).enter().call(svg_build_player);
            svg.select('.player').attr('transform', 'translate(10 9)');
            el
                .append($('<span/>').addClass('name').text(player.name))
                .append($('<span/>').addClass('score'))
            ;
            legend.append(el);
            i++;
        }

        // UI handlers
        el_previous.click(function () {
            event_ind--;
            el_turn_slider.val(event_ind).trigger('change');
        });

        el_next.click(function () {
            event_ind++;
            el_turn_slider.val(event_ind).trigger('change');
        });

        el_turn_slider.change(function () {
            event_ind = parseInt(el_turn_slider.val());
            el_previous.prop('disabled', event_ind <= 0);
            el_next.prop('disabled', event_ind >= events.length - 1);
            el_turn_label.text(events[event_ind].turn[0] + ' (' + event_ind + ')');
            render_turn(events[event_ind]);
        });
        el_turn_slider.attr('min', 0).attr('max', events.length - 1).val(0);
        el_turn_slider.trigger('change');

        el_playpause.click(function () {
            playing = !playing;
            el_playpause
                .find('span').text(playing ? 'Pause' : 'Lecture');
            el_playpause
                .find('i')
                .toggleClass('fa-play', !playing)
                .toggleClass('fa-pause', playing);
            if (playing) {
                playing_timer = setInterval(function () {
                    event_ind++;
                    if (event_ind >= events.length) {
                        event_ind = events.length - 1;
                        clearInterval(playing_timer); // just to be sure
                        playing = true; // trigger pause
                        el_playpause.trigger('click');
                        return;
                    }
                    el_turn_slider.val(event_ind).trigger('change');
                }, EVENT_DURATION);
            } else {
                clearInterval(playing_timer);
            }
        });

        // we are ready, trigger a fake playpause to init everything
        playing = true;
        el_playpause.trigger('click');

        // and we can now reveal the UI
        el_replay.show();
    });

});
