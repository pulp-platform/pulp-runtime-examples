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




	L1_DATA uint8_t W2_su[(IFM_CH_NN * DIM_KER_SUBBYTE * DIM_KER_SUBBYTE * OFM_CH) >> 2]=WEIGHTS_2_SU;
	L1_DATA int8_t  X2_su[(OUT_PIX * IFM_CH_NN* DIM_KER_SUBBYTE  * DIM_KER_SUBBYTE) >> 2]= IFM_2_SU;
	L1_DATA int32_t Y2_su[(OFM_CH * OUT_PIX)] = {0};
	L1_DATA int32_t O2_su[(OFM_CH * OUT_PIX)] = OFM_2_SU; // Golden model
