#include "../include/trie.h"

trie_node * trie_init() {
  trie_node * trie = NULL;
  trie = malloc(sizeof(trie_node));
  TESTMEM(trie);
  memset(trie,0,sizeof(trie_node));

  return trie;
}


void trie_init_prox(trie_node * trie) {
  trie->prox = malloc(sizeof(trie_node*)*(TRIE_END_CHAR - TRIE_START_CHAR + 1));
  TESTMEM(trie->prox);
  memset(trie->prox,0,sizeof(trie_node*)*(TRIE_END_CHAR - TRIE_START_CHAR + 1));
}

//private auxiliar function to keep code readable. assumes root->append!=NULL, and s<strlen(root->append)

//TODO: ALTER TRIE INSERTION MECHANISM TO STOP CUTTING ENDNODES
void trie_split_insert(trie_node * root, int s, char * word) {
  trie_node * aux;
  char * caux;

  aux           = trie_init();
  aux->endnode  = root->endnode;
  aux->prox     = root->prox;
  aux->append   = NULL;
  if (s+1 != strlen(root->append)) {
    aux->append = malloc((strlen(root->append)-s)*sizeof(char));
    TESTMEM(aux->append);
    strcpy(aux->append, root->append+s+1);
  }
  root->endnode = 0;
  root->prox    = NULL;
  trie_init_prox(root);
  root->prox[root->append[s] - TRIE_START_CHAR] = aux;
  if (s>0) {
    caux = malloc((s+1) * sizeof(char));
    TESTMEM(caux);
    strncpy(caux, root->append, s);
    caux[s]='\0';
    free(root->append);
    root->append = caux;
  } else {
    free(root->append);
    root->append = NULL;
  }

  if (s == strlen(word)) {
    root->endnode = 1;
  } else {
    root->prox[word[s] - TRIE_START_CHAR] = trie_insert(root->prox[word[s] - TRIE_START_CHAR], word+s+1);
  }
}


trie_node * trie_insert(trie_node * root, char * word) {
  int s=0;
  if (root==NULL)
    root = trie_init();

  if (root->append == NULL) {
    if (root->prox == NULL && !root->endnode) {
      if (*word!='\0') {
        root->append = malloc((strlen(word)+1) * sizeof(char));
        TESTMEM(root->append);
        strcpy(root->append, word);
      }
      root->endnode = 1;
    } else {
      if (*word=='\0') {
        root->endnode = 1;
      } else {
        if (root->prox==NULL) trie_init_prox(root);
        root->prox[*word - TRIE_START_CHAR] = trie_insert(root->prox[*word - TRIE_START_CHAR], word+1);
      }
    }
    return root;
  }


//Se chegarmos aqui, estamos num no comprimido
  while (word[s] == root->append[s]) {
    if (word[s]=='\0') { //they are equal
      root->endnode = 1;
      return root;
    }
    s++;
  }

  //word is bigger than append, we continue on next node
  if (root->append[s]=='\0') {
    if (root->prox==NULL) trie_init_prox(root);
    root->prox[word[s] - TRIE_START_CHAR] = trie_insert(root->prox[word[s] - TRIE_START_CHAR], word+s+1);
    return root;
  }

  //either append is bigger than word, or they differ now, or a substr of append should be final - a split occurs
  trie_split_insert(root, s, word);
  return root;
}


int trie_search(trie_node * root, char * word) {
  trie_iterator it = it_init(root);
  while (*word!='\0') {
    if (it_travel(&it, *word))
      return 0;
    word ++;
  }
  return (it_isendnode(&it));
}

void trie_destroy(trie_node * root) {
  int i;
  if (root==NULL)
    return;
  if (root->prox != NULL) {
    for (i=0; i<=TRIE_END_CHAR - TRIE_START_CHAR; i++) {
      trie_destroy(root->prox[i]);
    }
    free(root->prox);
  }
  if (root->append!=NULL)
    free(root->append);
  free(root);
}


trie_iterator it_init(trie_node * root) {
  trie_iterator it;
  it.pos  = 0;
  it.node = root;
  return it;
}

int it_travel(trie_iterator * it, char c) {
  if (it->node->append == NULL || it->node->append[it->pos]=='\0') {
    if (it->node->prox[c - TRIE_START_CHAR] == NULL) {
      return 1;
    } else {
      it->pos  = 0;
      it->node = it->node->prox[c - TRIE_START_CHAR];
      return 0;
    }
  } else {
    if (it->node->append[it->pos]==c) {
      it->pos += 1;
      return 0;
    } else {
      return 1;
    }
  }
}

int it_isendnode(trie_iterator * it) {
  if (it->node->append == NULL || it->node->append[it->pos]=='\0') {
    return (it->node->endnode == 1);
  } else {
    return 0;
  }
}
