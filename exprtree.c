struct tnode* makeLeafNode(int n){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->op = NULL;
    temp->val = n;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct tnode* newfucntion(){
printf("hi");
}
struct tnode* makeOperatorNode(char c,struct tnode *l,struct tnode *r){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->op = malloc(sizeof(char));
    *(temp->op) = c;
    temp->left = l;
    temp->right = r;
    return temp;
}

int evaluate(struct tnode *t){
    if(t->op == NULL){
        return t->val;
    }
    else{
        switch(*(t->op)){
            case '+' : return evaluate(t->left) + evaluate(t->right);
                       break;
            case '-' : return evaluate(t->left) - evaluate(t->right);
                       break;
            case '*' : return evaluate(t->left) * evaluate(t->right);
                       break;
            case '/' : return evaluate(t->left) / evaluate(t->right);
                       break;
        }
  
}
}

void prefix(struct tnode *t){
	if(t->op==NULL)
	printf("%d",t->val);
	else
	printf("%c",*(t->op));
	if(t->left!=NULL)
		prefix(t->left);
	if(t->right!=NULL)
		prefix(t->right);
	
}
int getreg(int *registerno)
{
*registerno=*registerno+1;
return *(registerno)-1;
}

void freereg(int *registerno)
{
 *(registerno)=*(registerno)-1;
}



int codegen(tnode *t,int *registerno)
{
	
	if(t->left==NULL && t->right==NULL)
	{
		int p=getreg(registerno);
		
		printf("MOV R%d, %d\n",p,t->val);
		return p;
	}
	else
	{
		int p=codegen(t->left,registerno);
		int q=codegen(t->right,registerno);
		if(*(t->op)=='+')
		{
		if(p<q)
		{
			printf("ADD R%d, R%d\n",p,q);
			freereg(registerno);
			return p;
		}
		else
		{printf("ADD R%d, R%d\n",q,p);
		freereg(registerno);
		return q;
		}
		}
		if(*(t->op)=='*')
		{
		if(p<q)
		{
			printf("MUL R%d, R%d\n",p,q);
			freereg(registerno);
			return p;
		}
		else
		{printf("MUL R%d, R%d\n",q,p);
		freereg(registerno);
		return q;
		}
		}
		
		if(*(t->op)=='-')
		{
		if(p<q)
		{
			printf("SUB R%d, R%d\n",p,q);
			freereg(registerno);
			return p;
		}
		else
		{printf("SUB R%d, R%d\n",q,p);
		freereg(registerno);
		return q;
		}
		}
		
		if(*(t->op)=='/')
		{
		if(p<q)
		{
			printf("DIV R%d, R%d\n",p,q);
			freereg(registerno);
			return p;
		}
		else
		{printf("DIV R%d, R%d\n",q,p);
		freereg(registerno);
		return q;
		}
		}
	}
}
		
	
		
void postfix(struct tnode *t)
{
if(t->left!=NULL)
postfix(t->left);
if(t->right!=NULL)
postfix(t->right);
if(t->op==NULL)
printf("%d",t->val);
else
printf("%c",*(t->op));
}
