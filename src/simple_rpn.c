#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct node 
{
  int data;
  struct node *next;
}node_t; 

typedef struct stack
{ 
  int position;
  struct node *pointer;
}stack_t;

stack_t *stack_create()
{ 
  stack_t *stack; 
  stack = (stack_t*)malloc(sizeof(stack_t));
  stack->pointer = NULL;
  stack->position = 0;
  return stack;
}

void push(stack_t *stack, int data)
{
  if(stack == NULL)
  {
    fprintf(stderr, "Error stack, function push\n");
    exit(-1);
  } 
  node_t *temp = (node_t*)malloc(sizeof(node_t));
  temp->data = data;

 if(stack->pointer == NULL)
 {
    temp->next = NULL;
    stack->pointer = temp;
 } else {
    temp->next = stack->pointer;
    stack->pointer = temp;
 }  
 stack->position++;
}  

int pop(stack_t *stack)
{ 
  int value = 0;
  if(!stack || !stack->pointer)
    {
      return 0;
    }
  value = stack->pointer->data;
  node_t *delete_element = stack->pointer;
  stack->pointer = stack->pointer->next;
  free(delete_element);
  stack->position--;
  return value;
}  

void delete_element_stack(node_t *element)
{
  if(element->next)
  {
    delete_element_stack(element->next);
  }
  free(element);
}  

void delete_stack(stack_t *stack)
{
  if(!stack)
  { 
    fprintf(stdout,"Success\n");
    return;
   }
  if(stack->pointer)
  {  
    delete_element_stack(stack->pointer);
  }
  free(stack);
}  

int size_stack(stack_t *stack)
{
  return stack->position;
} 

int stack_empty(stack_t *stack)
{
  return !stack->pointer;
} 

int rpn_calculator(stack_t *stack)
 {
  int sim = 0;
  int operand = 0;
  node_t *delete_element;
  while(!feof(stdin))
   { 
    sim = getchar();
    switch(sim)
     {
      case '\n':
      case ' ' :
        break;
      case 27 :
        while(!stack_empty(stack))
        {
           delete_element = stack->pointer;
           stack->pointer = stack->pointer->next;
           free(delete_element);
           stack->position--;
        }
        free(stack);
        exit(0);     
      case '=' : 
        fprintf(stdout, "result = %d\n", pop(stack));
      case '+' :
          push(stack, pop(stack) + pop(stack));
          break;
      case '-' : 
          push(stack, (pop(stack) - pop(stack)));
          break;
      case '*' :
          push(stack, pop(stack) * pop(stack));
          break;
      case '/' :
          push(stack, pop(stack) / pop(stack));
          break;
      default:
          ungetc(sim, stdin);
          if(fscanf(stdin, "%d", &operand) == 1)
          {
            push(stack, operand);
          } else 
          {
            perror("Integer ONLY");
            while(!stack_empty(stack))
            {
              delete_element = stack->pointer;
              stack->pointer = stack->pointer->next;
              free(delete_element);
              stack->position--;
            }
            free(stack);
            exit(-1);
          }
          break;
    }
  }
  return 0;
}

int main()
{
  stack_t *stack;
  stack = stack_create();
  rpn_calculator(stack);
  delete_stack(stack);
  free(stack);
  return 0;
}
