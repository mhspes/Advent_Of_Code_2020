#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static char fname[] = "inputs/aoc20.txt";
static FILE * fp;

#define TILES_MAX 150

// Only contains part 1

enum edges {
    TOP, LEFT, DOWN, RIGHT
};

struct tile;
struct neighbors {
    struct tile * tile_ptr;
    uint8_t edge;
    uint8_t reversed;
};

typedef struct tile {
    uint32_t ID;
    char tiledata[10][10];
    struct neighbors neighbors[4]; // neighbor tiles
    uint8_t edges[4];	// current position of original edges
    uint8_t flipped[4];
    uint8_t placed;
} TILE;

TILE tiles[TILES_MAX];
TILE * corners[4];

uint16_t n_tiles;


// Flip a tile around x axis
static void flip_tile_x(TILE * tile)
{
    uint8_t i, temp;
    char tdata[10][10];

    memcpy(tdata, tile->tiledata, sizeof(tdata));

    for(i = 0; i < 10; i++)
        memcpy(tile->tiledata[i], tdata[9-i], 10);

    // Flip positions of opposite edges
    temp = tile->edges[TOP];
    tile->edges[TOP] = tile->edges[DOWN];
    tile->edges[DOWN] = temp;

    tile->flipped[LEFT] = (tile->flipped[LEFT] + 1) % 2;
    tile->flipped[RIGHT] = (tile->flipped[RIGHT] + 1) % 2;
}

// Flip a tile around y axis
static void flip_tile_y(TILE * tile)
{
    uint8_t i, j, temp;
    char tdata[10][10];

    memcpy(tdata, tile->tiledata, sizeof(tdata));

    for(i = 0; i < 10; i++)
        for(j = 0; j < 10; j++)
            tile->tiledata[i][j] = tdata[i][9-j];

    // Flip positions of opposite edges
    temp = tile->edges[LEFT];
    tile->edges[LEFT] = tile->edges[RIGHT];
    tile->edges[RIGHT] = temp;

    tile->flipped[TOP] = (tile->flipped[TOP] + 1) % 2;
    tile->flipped[DOWN] = (tile->flipped[DOWN] + 1) % 2;


}

// Rotates a tile 90 degress clockwise
static void rotate(TILE * tile)
{
    int i, j;
    uint8_t temp;
    char tdata[10][10];

    memcpy(tdata, tile->tiledata, sizeof(tdata));

    // Rotate the pixels of the tile
    for(j = 9; 0 <= j; j--)
        for(i = 0; i <= 9; i++)
            tile->tiledata[i][j] = tdata[9-j][i];

    // Adjust edge positions
    temp = tile->edges[TOP];
    tile->edges[TOP] = tile->edges[LEFT];
    tile->edges[LEFT] = tile->edges[DOWN];
    tile->edges[DOWN] = tile->edges[RIGHT];
    tile->edges[RIGHT] = temp;

    // Adjust the flipped flags
    temp = tile->flipped[TOP];
    tile->flipped[TOP] = tile->flipped[LEFT];
    tile->flipped[LEFT] = tile->flipped[DOWN];
    tile->flipped[DOWN] = tile->flipped[RIGHT];
    tile->flipped[RIGHT] = temp;

}

// Compare left edge of a tile (ind1) to the right edge of a tile (ind2)
// ret 1 for a match
static int comp_edges(int ind1, int ind2)
{
    int i;
    for(i = 0; i < 10; i++)
        if(tiles[ind1].tiledata[i][0] != tiles[ind2].tiledata[i][9])
            return 0;

    return 1; // All elements matched
}

/* Connects the tiles as "neighbors". Also finds the matching edges
 * and if either of them is mirrored
 * param edge1 indicates which "direction" the matching tile is
 */
static void addneighbor(TILE * tile1, TILE * tile2, uint8_t edge1)
{
    uint8_t edge2, temp_edg;

    tile2->neighbors[edge1].tile_ptr = tile1;

    /* Find which edge of the rotated and flipped tile1 is compared,
     * check if reversed. */

    temp_edg = (edge1 + 2) % 4;
    edge2 = tile1->edges[temp_edg];

    if(tile1->flipped[(temp_edg) % 4] == 1)
    {
    	tile2->neighbors[edge1].reversed = 1;
    	tile1->neighbors[edge2].reversed = 1;
    }
    tile1->neighbors[edge2].tile_ptr = tile2;

}

/* Compare a tile (of index) to the upcoming tiles on the list
 * Add the found neighbors */
static void compare(int current)
{
    uint16_t comp;

    for(comp = current + 1; comp < n_tiles; comp++)
    {
        // Compare upper edge of current tile
        if(!memcmp(&tiles[current].tiledata[0], &tiles[comp].tiledata[9], 10))
        {
            addneighbor(&tiles[current],&tiles[comp], DOWN);
            continue;
        }
        // lower edge
        if(!memcmp(&tiles[current].tiledata[9], &tiles[comp].tiledata[0], 10))
        {
            addneighbor(&tiles[current],&tiles[comp], TOP);
            continue;
        }
        // left edge
        if(comp_edges(current, comp))
        {
            addneighbor(&tiles[current],&tiles[comp], RIGHT);
            continue;
        }
        // right edge
        if(comp_edges(comp, current))
        {
            addneighbor(&tiles[current],&tiles[comp], LEFT);
            continue;
        }

    }

}

// Part 1/2
static void part1()
{
    int i, j, counter;
    uint64_t prod = 1;

    for(i = 0; i < n_tiles; i++)
    {
        if(tiles[i].neighbors[0].tile_ptr != 0
                && tiles[i].neighbors[1].tile_ptr != 0
                && tiles[i].neighbors[2].tile_ptr != 0
                && tiles[i].neighbors[3].tile_ptr != 0) continue;
        // All possible neighbors already found..

        compare(i);
        flip_tile_y(&tiles[i]);
        compare(i);

        rotate(&tiles[i]);
        compare(i);
        flip_tile_x(&tiles[i]);
        compare(i);

        rotate(&tiles[i]);
        compare(i);
        flip_tile_y(&tiles[i]);
        compare(i);

        rotate(&tiles[i]);
        compare(i);
        flip_tile_x(&tiles[i]);
        compare(i);

        rotate(&tiles[i]); // Back to original orientation
    }

    for(i = 0, j = 0; i < n_tiles; i++)
    {
        counter = 0;
        if(tiles[i].neighbors[0].tile_ptr != 0)
        {
            counter++;
        }
        if(tiles[i].neighbors[1].tile_ptr != 0)
        {
            counter++;
        }
        if(tiles[i].neighbors[2].tile_ptr != 0)
        {
            counter++;
        }
        if(tiles[i].neighbors[3].tile_ptr != 0)
        {
            counter++;
        }

        if(counter == 2)
        {
            if(j > 3)
            {
                printf("Failed..\n");
                exit(0);
            }
            printf("Corner tile found: %d\n", tiles[i].ID);
            prod *= tiles[i].ID;
            corners[j++] = &tiles[i];
        }

    }
    printf("Part 1: %llu \n", prod);

}


void aoc20()
{
    int i, j;

    memset(tiles, 0, sizeof(tiles));

    if(NULL == ( fp = fopen(fname, "r")))
    {
        perror(fname);
        exit(0);
    }

    memset(tiles, 0, sizeof(tiles));
    n_tiles = 0;
    // Read input
    while(EOF != fscanf(fp, "Tile %d:\n", &tiles[n_tiles].ID))
    {
        // Read the tile data
        for(i = 0; i < 10; i++)
        {
            for(j = 0; j < 10; j++)
            {
                tiles[n_tiles].tiledata[i][j] = fgetc(fp);
            }
            fgetc(fp); // read linebreak
        }

        fgetc(fp); // read linebreak
        n_tiles++;
    }

    for(i = 0; i < n_tiles; i++)
    {
    	tiles[i].edges[TOP] = TOP;
    	tiles[i].edges[LEFT] = LEFT;
    	tiles[i].edges[DOWN] = DOWN;
    	tiles[i].edges[RIGHT] = RIGHT;
    }
    part1();
    //part2();
}
