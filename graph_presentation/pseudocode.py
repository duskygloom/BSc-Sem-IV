from typing import Literal, List, Self

WHITE = GRAY = BLACK = NULL = 0

timestamp = 0

def enqueue():
    ...

def dequeue():
    ...

def is_queue_empty():
    ...

class Vertex:
    # default attributes
    value: int
    adjacent: List[Self]
    # additional attributes
    color: Literal["WHITE", "GRAY", "BLACK"]
    depth: int
    parent: Self

def BFS(graph, source):
    # whiten all vertices
    for v in graph.vertices:
        v.color = WHITE
        v.parent = NULL
    # traverse source
    source.color = GRAY
    source.depth = 0
    source.parent = NULL
    enqueue(source)
    # keep dequeuing
    while not is_queue_empty():
        curr = dequeue()
        # traverse nodes adjacent to source
        for v in curr.adjacent:
            if v.color == WHITE:
                v.color = GRAY
                v.depth = curr.depth + 1
                v.parent = curr
                enqueue(v)

def DFS_VISIT(vertex):
    global timestamp
    # increase timestamp
    timestamp += 1
    vertex.discovered = timestamp
    vertex.color = GRAY
    for v in vertex.adjacent:
        if v.color == WHITE:
            v.parent = vertex
            DFS_VISIT(v)
    vertex.finished = timestamp
    vertex.color = BLACK

def DFS(graph):
    global timestamp
    # whiten all vertices
    for v in graph.vertices:
        v.color = WHITE
        v.parent = NULL
    # reset timestamp
    timestamp = 0
    # visit every vertex
    for v in graph.vertices:
        if v.color == WHITE:
            DFS_VISIT(graph, v)

def TOPOLOGICAL_VISIT(vertex, stack):
    global timestamp
    # increase timestamp
    timestamp += 1
    vertex.color = GRAY
    for v in vertex.adjacent:
        if v.color == WHITE:
            DFS_VISIT(v)
    vertex.finished = timestamp
    stack.push_front(vertex)
    vertex.color = BLACK

def TOPOLOGICAL_SORT(graph):
    global timestamp
    stack = []
    # whiten all vertices
    for v in graph.vertices:
        v.color = WHITE
    # reset timestamp
    timestamp = 0
    # visit every vertex
    for v in graph.vertices:
        if v.color == WHITE:
            TOPOLOGICAL_VISIT(v, stack)

class Graph():
    vertices: List[Vertex]

def TRANSPOSE(graph):
    transpose = Graph()
    for v in graph.vertices:
        for u in v.adjacent:
            graph.vertex[u] = v
    return transpose

def STRONGLY_CONNECTED_COMPONENTS(graph):
    DFS(graph)
    TOPOLOGICAL_SORT(graph)
    transpose = TRANSPOSE(graph)
    # each tree in the forest is a strongly
    # connected component
    DFS(transpose)
    forest = transpose.forest
    return forest