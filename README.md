# GraphVizTemplate
Basic usage of GraphViz:
 1. Create GraphViz context
 2. Create graph
 3. Add content to graph (nodes, edges, attributes)
 4. Choose layout algorithm for the rendering
 5. Render graph
 6. Repeat 4. and 5. to rerender the same graph (maybe with another layout algorithm)
 7. Close graph if it isn't needed anymore (after this it could cause segfault if you try to use the graph again)
 8. Free GraphViz context (it can cause segfault too if you try to use the gvc again)