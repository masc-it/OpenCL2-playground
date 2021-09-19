__kernel void process_array(__global int* in_arr, __global int* out_arr) {
  
  out_arr[get_global_id(0)] = in_arr[get_global_id(0)] * 2;
  in_arr[get_global_id(0)] = in_arr[get_global_id(0)] - 1;

}