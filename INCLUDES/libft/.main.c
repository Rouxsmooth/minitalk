/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:00:51 by mzaian            #+#    #+#             */
/*   Updated: 2025/02/01 03:23:45 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "INCLUDES/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void del_2d_array(void **array, int len);
void del_3d_array(void ***array, int len, int *insidelens);
void *ft_calloc(size_t count, size_t size);
void ft_del(void *ptr);

int main(void)
{
    int i, j, k;
    int rows = 3, cols = 3, depth = 2;
    
    // Allocate and fill a 2D array
    int **array2D = ft_calloc(rows, sizeof(int *));
    for (i = 0; i < rows; i++)
    {
        array2D[i] = ft_calloc(cols, sizeof(int));
        for (j = 0; j < cols; j++)
            array2D[i][j] = i * cols + j;
    }
    
    // Print 2D array before deletion
    printf("2D Array before deletion:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            printf("%d ", array2D[i][j]);
        printf("\n");
    }
    
    // Delete 2D array
    del_2d_array((void **)array2D, rows);
    
    // Allocate and fill a 3D array
    int ***array3D = ft_calloc(depth, sizeof(int **));
    int *insidelens = ft_calloc(depth, sizeof(int)); // Track inner sizes
    for (i = 0; i < depth; i++)
    {
        array3D[i] = ft_calloc(rows, sizeof(int *));
        insidelens[i] = rows;
        for (j = 0; j < rows; j++)
        {
            array3D[i][j] = ft_calloc(cols, sizeof(int));
            for (k = 0; k < cols; k++)
                array3D[i][j][k] = i * rows * cols + j * cols + k;
        }
    }
    
    // Print 3D array before deletion
    printf("\n3D Array before deletion:\n");
    for (i = 0; i < depth; i++)
    {
        printf("Depth %d:\n", i);
        for (j = 0; j < rows; j++)
        {
            for (k = 0; k < cols; k++)
                printf("%d ", array3D[i][j][k]);
            printf("\n");
        }
    }
    
    // Delete 3D array
    del_3d_array((void ***)array3D, depth, insidelens);
    
    // Free inside length tracker
    free(insidelens);
    
    return 0;
}
