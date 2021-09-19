__kernel void hello_world(__global char* data) {
  
  data[0] = 'H';
  data[1] = 'i';
  data[2] = '!';
  data[3] = '\n';
}