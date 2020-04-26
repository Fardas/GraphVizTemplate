#include <iostream>
#include <string>
#include <gvc.h>

/*
 * Basic usage of GraphViz:
 * 1. Create GraphViz context
 * 2. Create graph
 * 3. Add content to graph (nodes, edges, attributes)
 * 4. Choose layout algorithm for the rendering
 * 5. Render graph
 * 6. Repeat 4. and 5. to rerender the same graph (maybe with another layout algorithm)
 * 7. Close graph if it isn't needed anymore (after this it could cause segfault if you try to use the graph again)
 * 8. Free GraphViz context (it can cause segfault too if you try to use the gvc again)
*/

int main()
{
    // 1. Create GraphViz context
    // GraphViz context: one per application, contains attributes independent of any particular graph
    GVC_t *gvc;
    gvc = gvContext();

    // 2. Create graph
    // Open graph with the graph name and graph type
    Agraph_t *graph;
    std::string graphName = "TwoWayRing";
    Agdesc_t graphType = Agdirected;
    graph = agopen(const_cast<char*>(graphName.c_str()), graphType, 0);

    // 3. Add content to graph (nodes, edges, attributes)
    short length = 20;
    Agnode_t *nodes[length];
    Agedge_t *edges[length * 2];

    // Nodes
    for(int i = 0; i < length; i++)
    {
        char str[(((sizeof i) * CHAR_BIT) + 2)/3 + 2];
        sprintf(str, "%d", i);

        // Adding nodes to graph
        nodes[i] = agnode(graph, str, true);
    }

    // Edges
    for(int i = 0; i < length; i++)
    {
        char str[(((sizeof i) * CHAR_BIT) + 2)/3 + 2];
        sprintf(str, "%d", i);

        // Adding edges to graph
        edges[i] = agedge(graph, nodes[i], nodes[(i + 1) % length], str, true);
        edges[length + i] = agedge(graph, nodes[(i + 1) % length], nodes[i], str, true);

        // Adding color attributes to edges
        agsafeset(edges[i], "color", "blue", "");
        agsafeset(edges[length + i], "color", "red", "");
    }

    // Setup layout and file names for rendering
    std::string graphLayouts[2] = {"dot", "circo"};
    std::string filenames[2] = {"dot.png", "circo.png"};

    // 6. Repeat 4. and 5. to rerender the same graph (maybe with another layout algorithm)
    for(int i = 0; i < 2; i++)
    {
        // 4. Choose layout algorithm for the rendering
        // Passes graph to one of the layout algorithms
        gvLayout(gvc, graph, const_cast<char*>(graphLayouts[i].c_str()));

        // 5. Render graph
        // In CodeCompass gvRenderData is used for in-memory rendering
        gvRenderFilename(gvc, graph, "png", const_cast<char*>(filenames[i].c_str()));

        // Cleanup layout information: after each layout render
        gvFreeLayout(gvc, graph);
    }

    // 7. Close graph if it isn't needed anymore (after this it could cause segfault if you try to use the graph again)
    agclose(graph);

    // 8. Free GraphViz context (it can cause segfault too if you try to use the gvc again)
    return (gvFreeContext(gvc));
}
