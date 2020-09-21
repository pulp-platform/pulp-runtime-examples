/*
 * test_data_allocation.h
 * Angelo Garofalo <angelo.garofalo@unibo.it>
 *
 * Copyright (C) 2019 University of Bologna
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef __PULP_NN_TEST_DATA_ALLOCATION__
#define __PULP_NN_TEST_DATA_ALLOCATION__
#endif

#define IFM_CH 4
#define DIM_KER 3
#define OFM_CH 4
#define OUT_PIX 2

#define DIM_KER_SUBBYTE 4

#define DIM_KER_NN	3
#define IFM_CH_NN	32
#define OFM_CH_NN	4
#define OUT_PIX_NN	2




	// L1_DATA uint8_t W8_su[(IFM_CH * DIM_KER * DIM_KER * OFM_CH)] = WEIGHTS_8_SU;
	// L1_DATA int8_t X8_su[(OUT_PIX * IFM_CH * DIM_KER  * DIM_KER)] = IFM_8_SU;
	// L1_DATA int32_t Y8_su[(OFM_CH * OUT_PIX)] = {0};
	// L1_DATA int32_t O8_su[(OFM_CH * OUT_PIX)] = OFM_8_SU; // Golden model

	L1_DATA uint8_t filters_3d[(IFM_CH_NN * DIM_KER_NN * DIM_KER_NN * OFM_CH_NN)] = WEIGHTS_PULPNN_K;
	L1_DATA int8_t buffer_im2col[(OUT_PIX_NN * IFM_CH_NN * DIM_KER_NN  * DIM_KER_NN)] = IFM_PULPNN_K;
	L1_DATA int32_t matmul_out[(OFM_CH_NN * OUT_PIX_NN)] = {0};
	L1_DATA int32_t golden_matmul_out[(OFM_CH_NN * OUT_PIX_NN)] = OFM_PULPNN_K; // Golden model
