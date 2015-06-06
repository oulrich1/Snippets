function countAdjacentAlive( cells, row, col )
{
  var nAliveCount = 0;
  
  // assume 8 adjacent
  for ( var r = (row-1); r <= (row+1); ++r )
  {
    for ( var c = (col-1); c <= (col+1); ++c )
    {
      /// skip if out of bounds of kernel or if at  row and col (center of kernel)
      if ( (r < 0 || r >= cells.length) ||
           (c < 0 || c >= cells[r].length) ||
           (r == row && c == col) )
       {
        continue;
       }
      
      if ( cells[r][c] )
      {
        nAliveCount++;
      }
    }
  }  // end for
  
  return nAliveCount;
}

// check for exactly 2 or 3 adjacent alive cells, if so then stay alive.. // otherwise die
function doAlive( cellsCopy, cellsOriginal, row, col )
{
  var nAdjacentAlive = countAdjacentAlive( cellsOriginal, row, col );
  
  if ( nAdjacentAlive != 2 && nAdjacentAlive != 3 )
  {
    cellsCopy[row][col] = 0; // not enough or too many nearby alive cells, die
  }
}

// check if there are exactly 3 live neighbors if so then become alive
function doDead( cellsCopy, cellsOriginal, row, col )
{  
  if ( countAdjacentAlive(cellsOriginal, row, col) == 3 )
  {
    cellsCopy[row][col] = 1; // redproduce in this case
  }
}

function nextGen(cells) {
  // Uncomment next row to have an example
  // N x M
  var cellsCopy = [];
  for (var i = 0; i < cells.length; i++) {
    cellsCopy.push( [].concat(cells[i]) );
  };
  
  // iteratoe over each cell in the original cells matrix 
  for ( var row = 0; row < cells.length; ++row )
  {
    for ( var col = 0; col < cells.length; ++col )
    {
      if ( cells[row][col] != 0 )
      {
        doAlive( cellsCopy, cells, row, col );
      }
      else
      {
        doDead( cellsCopy, cells, row, col );
      }
    }
  }
  return cellsCopy;
}
