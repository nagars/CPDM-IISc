#include "dma.h"

void dma_register_callbacks(DMA_HandleTypeDef * _hdma,
		void (*transfer_complete_cb)(DMA_HandleTypeDef*),
		void (*transfer_failure_cb)(DMA_HandleTypeDef*)){

	//Configure DMA success callback
	HAL_DMA_RegisterCallback (_hdma,
			HAL_DMA_XFER_CPLT_CB_ID , transfer_complete_cb);

	//Configure DMA failure callback
	HAL_DMA_RegisterCallback (_hdma,
			HAL_DMA_XFER_ERROR_CB_ID , transfer_failure_cb);

	return;
}

