import numpy as np
import scipy as sci

import errno
import os

from scipy import sparse


def from_file_to_csr(filename: str):
    if not os.path.isfile(filename):
        raise FileNotFoundError(
            errno.ENOENT, os.strerror(errno.ENOENT), filename)

    if filename.endswith('.mtx'):
        graph = read_mtx_file(filename)
    elif filename.endswith('.txt'):
        graph = read_txt_file(filename)
    elif filename.endswith('.gr'):
        graph = read_gr_file(filename)
    else:
        raise ValueError("Unsupported file format")

    return graph


def read_mtx_file(filename: str):
    rows = list()
    cols = list()
    added = set()
    num_vert = 0
    loop_count = 0
    duplicates = 0

    f = open(filename, "r")

    first_line = True

    for line in f:
        if line.startswith("%"):
            continue

        if first_line:
            first_line = False
            num_vert = int(line.split()[0])
            continue

        edge = line.split(' ')
        e_from = int(edge[0]) - 1
        e_to = int(edge[1]) - 1

        if e_from == e_to:
            loop_count += 1
            continue

        if not (e_from, e_to) in added:
            rows.append(e_from)
            cols.append(e_to)
            added.add((e_from, e_to))
        else:
            duplicates += 1

        if not (e_to, e_from) in added:
            rows.append(e_to)
            cols.append(e_from)
            added.add((e_to, e_from))
        else:
            duplicates += 1

    f.close()
    return sci.sparse.csr_matrix((np.zeros(len(rows)), (rows, cols)), shape=(num_vert, num_vert)), num_vert


def read_txt_file(filename: str):
    rows = list()
    cols = list()
    added = set()
    num_vert = 0
    loop_count = 0
    duplicates = 0

    f = open(filename, "r")

    for line in f:
        if line.startswith("#"):
            if "Nodes:" and "Edges:" in line:
                words = line.split(" ")
                for word in words:
                    if word.isnumeric():
                        num_vert = int(word)
                        break

            continue

        edge = line.split('\t')
        e_from = int(edge[0])
        e_to = int(edge[1])

        if e_from == e_to:
            loop_count += 1
            continue

        if not (e_from, e_to) in added:
            rows.append(e_from)
            cols.append(e_to)
            added.add((e_from, e_to))
        else:
            duplicates += 1

        if not (e_to, e_from) in added:
            rows.append(e_to)
            cols.append(e_from)
            added.add((e_to, e_from))
        else:
            duplicates += 1

    f.close()
    return sci.sparse.csr_matrix((np.zeros(len(rows)), (rows, cols)), shape=(num_vert, num_vert)), num_vert


def read_gr_file(filename: str):
    rows = list()
    cols = list()
    added = set()
    num_vert = 0
    loop_count = 0
    duplicates = 0

    f = open(filename, "r")

    for line in f:

        if line.startswith("p"):
            graph_info = line.split(" ")
            num_vert = int(graph_info[2])

        if line.startswith("a"):
            edge = line.split(' ')
            e_from = int(edge[1]) - 1
            e_to = int(edge[2]) - 1

            if e_from == e_to:
                loop_count += 1
                continue

            if not (e_from, e_to) in added:
                rows.append(e_from)
                cols.append(e_to)
                added.add((e_from, e_to))
            else:
                duplicates += 1

            if not (e_to, e_from) in added:
                rows.append(e_to)
                cols.append(e_from)
                added.add((e_to, e_from))
            else:
                duplicates += 1
    f.close()
    return sci.sparse.csr_matrix((np.zeros(len(rows)), (rows, cols)), shape=(num_vert, num_vert)), num_vert


def write_csr_to_bin_file(csr_mat: sci.sparse.csr_matrix, num_vertices: int, filename: str):
    f = open(filename, "wb")

    info = np.array([num_vertices, len(csr_mat.indices)], np.int32)

    info.tofile(f)
    csr_mat.indptr.tofile(f)
    csr_mat.indices.tofile(f)

    f.close()

    return


def write_csr_to_txt_file(csr_mat: sci.sparse.csr_matrix, num_vertices: int, filename: str):
    f = open(filename, "w")

    f.write(str(num_vertices) + " " + str(len(csr_mat.indices)) + '\n')

    for i in range(0, len(csr_mat.indices)):
        if i == len(csr_mat.indices) - 1:
            f.write(str(csr_mat.indices[i]) + '\n')
        else:
            f.write(str(csr_mat.indices[i]) + ' ')

    for i in range(0, len(csr_mat.indptr)):
        if i == len(csr_mat.indptr) - 1:
            f.write(str(csr_mat.indptr[i]))
        else:
            f.write(str(csr_mat.indptr[i]) + ' ')

    return

